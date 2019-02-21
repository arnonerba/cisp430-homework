//
//  Author: Arnon Erba
//  Assignment: Group 1 Strings
//  Objective: Develop five modules to replace some of the built-in
//  C/C++ string functions. Use char arrays to store strings. Input
//  strings are assumed to be of a fixed length.
//

#include <iostream>
#include <fstream>

using namespace std;

void stringCopy(char *A, char *B) {
    bool outOfBounds = false;
    int i = 0;
    while (!outOfBounds) {
        if (B[i] == '\0') {
            outOfBounds = true;
        }
        A[i] = B[i];
        i++;
    }
}

bool stringCompare(char *A, char *B) {
    bool outOfBounds = false;
    int i = 0;
    while (!outOfBounds) {
        if (A[i] == '\0' || B[i] == '\0') {
            outOfBounds = true;
        }
        if (A[i] != B[i]) {
            return false;
        }
        i++;
    }
    return true;
}

void stringConcatenation (char *A, char *B) {
    int i = 0;
    while (A[i] != '\0') {
        i++;
    }
    stringCopy(&A[i], B);
}

int stringPosition(char *A, char B) {
    bool outOfBounds = false;
    int i = 0;
    while (!outOfBounds) {
        if (A[i] == '\0') {
            outOfBounds = true;
        }
        if (A[i] == B) {
            return i;
        }
        i++;
    }
    return -1;
}

int stringLength(char *A) {
    int length = 0;
    while (A[length] != '\0') {
        length++;
    }
    for (int i = length; i > 0; i--) {
        A[i] = A[i-1];
    }
    A[0] = static_cast<char>(length);
    return length;
}

int main() {
    ifstream inputFile;
    char stringOne[32], stringTwo[32];
    char ch;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    inputFile >> stringOne >> stringTwo;
    stringCopy(stringOne, stringTwo);
    cout << stringOne << " " << stringTwo << endl;

    inputFile >> stringOne >> stringTwo;
    if (stringCompare(stringOne, stringTwo)) {
        cout << stringOne << " and " << stringTwo << " are identical" << endl;
    } else {
        cout << stringOne << " and " << stringTwo << " are not identical" << endl;
    }

    inputFile >> stringOne >> stringTwo;
    stringConcatenation(stringOne, stringTwo);
    cout << stringOne << " " << stringTwo << endl;

    inputFile >> stringOne >> ch;
    cout << ch << " is at position " << stringPosition(stringOne, ch) << " of " << stringOne << endl;

    inputFile >> stringOne;
    stringLength(stringOne);
    cout << stringOne << " has length " << static_cast<int>(stringOne[0]) << endl;

    inputFile.close();
    return 0;
}
