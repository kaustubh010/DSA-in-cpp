#!/usr/bin/env python3
"""
ghost_commits.py
────────────────
Push an empty commit to every repo in your GitHub account so they show
up in the contribution graph.

Requirements:
    pip install requests gitpython

Usage:
    python ghost_commits.py --token <GITHUB_PAT> [options]

Options:
    --token     GitHub Personal Access Token (needs repo scope)
    --message   Commit message  (default: "chore: restore contribution graph")
    --delay     Seconds to wait between repos  (default: 5)
    --dry-run   List repos without pushing anything
    --exclude   Comma-separated list of repo names to skip  e.g. old-repo,fork-repo
"""

import argparse
import sys
import time
import tempfile
import os
import logging
from pathlib import Path

import requests
from git import Repo, GitCommandError

# ── Logging ──────────────────────────────────────────────────────────────────
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s  %(levelname)-8s  %(message)s",
    datefmt="%H:%M:%S",
)
log = logging.getLogger("ghost_commits")


# ── GitHub API helpers ────────────────────────────────────────────────────────
def get_all_repos(token: str) -> list[dict]:
    """Fetch every repo owned by the authenticated user (handles pagination)."""
    headers = {
        "Authorization": f"Bearer {token}",
        "Accept": "application/vnd.github+json",
    }
    repos: list[dict] = []
    page = 1

    while True:
        resp = requests.get(
            "https://api.github.com/user/repos",
            headers=headers,
            params={"per_page": 100, "page": page, "affiliation": "owner"},
            timeout=15,
        )
        resp.raise_for_status()
        batch = resp.json()
        if not batch:
            break
        repos.extend(batch)
        page += 1

    return repos


def get_default_branch(token: str, owner: str, repo: str) -> str:
    headers = {
        "Authorization": f"Bearer {token}",
        "Accept": "application/vnd.github+json",
    }
    resp = requests.get(
        f"https://api.github.com/repos/{owner}/{repo}",
        headers=headers,
        timeout=10,
    )
    resp.raise_for_status()
    return resp.json().get("default_branch", "main")


# ── Core logic ────────────────────────────────────────────────────────────────
def push_empty_commit(
    clone_url_with_token: str,
    branch: str,
    message: str,
    author_name: str,
    author_email: str,
) -> None:
    """Clone repo into a temp dir, make an empty commit, and push."""
    with tempfile.TemporaryDirectory(prefix="ghost_") as tmpdir:
        log.debug("  Cloning into %s …", tmpdir)
        repo = Repo.clone_from(clone_url_with_token, tmpdir)

        # Configure identity for this repo
        repo.config_writer().set_value("user", "name", author_name).release()
        repo.config_writer().set_value("user", "email", author_email).release()

        # Checkout the default branch (already done by clone, but be explicit)
        repo.git.checkout(branch)

        # Empty commit – --allow-empty skips the "nothing to commit" guard
        repo.git.commit("--allow-empty", "-m", message)
        log.debug("  Committed. Pushing …")

        repo.remotes.origin.push(branch)


def build_auth_url(token: str, clone_url: str) -> str:
    """Inject token into the HTTPS clone URL."""
    # https://github.com/user/repo.git → https://<token>@github.com/user/repo.git
    return clone_url.replace("https://", f"https://{token}@")


# ── Entry point ───────────────────────────────────────────────────────────────
def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--token",   required=True, help="GitHub Personal Access Token (repo scope)")
    parser.add_argument("--message", default="chore: restore contribution graph", help="Commit message")
    parser.add_argument("--delay",   type=float, default=5.0, help="Seconds between repos (default: 5)")
    parser.add_argument("--dry-run", action="store_true", help="List repos without pushing")
    parser.add_argument("--exclude", default="", help="Comma-separated repo names to skip")
    args = parser.parse_args()

    excluded = {r.strip() for r in args.exclude.split(",") if r.strip()}

    # ── Fetch user info ───────────────────────────────────────────────────────
    log.info("Authenticating …")
    me_resp = requests.get(
        "https://api.github.com/user",
        headers={"Authorization": f"Bearer {args.token}", "Accept": "application/vnd.github+json"},
        timeout=10,
    )
    me_resp.raise_for_status()
    me = me_resp.json()
    username   = me["login"]
    user_email = me.get("email") or f"{username}@users.noreply.github.com"
    log.info("Logged in as: %s <%s>", username, user_email)

    # ── Fetch repos ───────────────────────────────────────────────────────────
    log.info("Fetching repository list …")
    repos = get_all_repos(args.token)
    log.info("Found %d repositories.", len(repos))

    if args.dry_run:
        log.info("── DRY RUN – no commits will be pushed ──")
        for r in repos:
            skip = " [SKIP – excluded]" if r["name"] in excluded else ""
            log.info("  %s%s", r["full_name"], skip)
        return

    # ── Push empty commits ────────────────────────────────────────────────────
    success, skipped, failed = 0, 0, 0

    for i, repo in enumerate(repos, 1):
        name = repo["name"]
        full = repo["full_name"]

        if name in excluded:
            log.info("[%d/%d] SKIP  %s (excluded)", i, len(repos), full)
            skipped += 1
            continue

        if repo.get("archived"):
            log.info("[%d/%d] SKIP  %s (archived)", i, len(repos), full)
            skipped += 1
            continue

        log.info("[%d/%d] %-45s …", i, len(repos), full)

        try:
            branch     = get_default_branch(args.token, username, name)
            auth_url   = build_auth_url(args.token, repo["clone_url"])
            push_empty_commit(auth_url, branch, args.message, username, user_email)
            log.info("  ✓  Pushed empty commit to '%s'", branch)
            success += 1
        except GitCommandError as exc:
            log.warning("  ✗  Git error on %s: %s", full, exc.stderr.strip())
            failed += 1
        except requests.HTTPError as exc:
            log.warning("  ✗  HTTP error on %s: %s", full, exc)
            failed += 1
        except Exception as exc:  # noqa: BLE001
            log.warning("  ✗  Unexpected error on %s: %s", full, exc)
            failed += 1

        # Rate-limit guard: sleep between repos (skip after last one)
        if i < len(repos):
            log.debug("  Waiting %.1fs …", args.delay)
            time.sleep(args.delay)

    # ── Summary ───────────────────────────────────────────────────────────────
    log.info("")
    log.info("═" * 50)
    log.info("  Done.  ✓ %d pushed   ⊘ %d skipped   ✗ %d failed", success, skipped, failed)
    log.info("═" * 50)
    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()