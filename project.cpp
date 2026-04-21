#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void displayFile(string filename) {
    ifstream file(filename);
    string line;

    if (!file) {
        cout << "File does not exist.\n";
        return;
    }

    cout << "\n----- File Content -----\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    cout << "------------------------\n";

    file.close();
}

void writeFile(string filename) {
    ofstream file(filename, ios::app);
    string line;

    cout << "Enter text (type END to stop):\n";

    while (true) {
        getline(cin, line);

        if (line == "END")
            break;

        file << line << endl;
    }

    file.close();
    cout << "Text saved successfully.\n";
}

int main() {
    string filename;
    int choice;

    cout << "Enter file name (example: notes.txt): ";
    cin >> filename;
    cin.ignore();

    do {
        cout << "\n===== SIMPLE TEXT EDITOR =====\n";
        cout << "1. View File\n";
        cout << "2. Add Text\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            displayFile(filename);
            break;

        case 2:
            writeFile(filename);
            break;

        case 3:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}