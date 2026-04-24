#include <bits/stdc++.h>
using namespace std;

int maxFrequency(vector<int>& nums, int k) {
  sort(nums.begin(), nums.end());
  int maxFreq = 0;
  int l = 0, sum = 0;
  for (int r = 0; r < nums.size(); r++) {
    sum += nums[r];
    while ((nums[r] * (r - l + 1) - sum) > k) {
      sum -= nums[l];
      l++;
    }
    maxFreq = max(maxFreq, r - l + 1);
  }
  return maxFreq;
}

int main() {
  vector<int> nums = {1, 2, 4};
  int k = 5;
  cout<< maxFrequency(nums, k);
  return 0;
}