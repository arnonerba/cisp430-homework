//
//  Author: Arnon Erba
//  Assignment: Group 8 Sort Search
//  Objective: Sort a global two-dimensional array using
//  bubble sort, selection sort, shell sort, and insertion
//  sort. Use binary search on the last row of the array.
//

#include <iostream>
#include <iomanip>

using namespace std;

const int ROWS = 5;
const int COLS = 4;
int a[ROWS][COLS];

void initializeArray() {
    a[0][0] = 5;
    a[0][1] = 3;
    a[0][2] = 2;
    a[0][3] = 16;
    a[1][0] = 9;
    a[1][1] = 8;
    a[1][2] = 10;
    a[1][3] = 17;
    a[2][0] = 4;
    a[2][1] = 7;
    a[2][2] = 11;
    a[2][3] = 18;
    a[3][0] = 2;
    a[3][1] = 5;
    a[3][2] = 9;
    a[3][3] = 12;
    a[4][0] = 7;
    a[4][1] = 9;
    a[4][2] = 4;
    a[4][3] = 10;
}

void displayArray() {
    for (int i = 0; i < ROWS; i++) {
        cout << "+---------------------------+" << endl;
        for (int j = 0; j < COLS; j++) {
            cout << '|' << setw(5) << a[i][j] << ' ';
        }
        cout << '|' << endl;
    }
    cout << "+---------------------------+" << endl;
}

void bubbleSort() {
    int temp, index;
    for (int limit = ROWS-1; limit > 0; limit--) {
        for (index = 0; index < limit; index++) {
            if (a[index][0] > a[index+1][0]) {
                for (int i = 0; i < COLS; i++) {
                    temp = a[index][i];
                    a[index][i] = a[index+1][i];
                    a[index+1][i] = temp;
                }
            }
        }
    }
}

void selectionSort() {
    int temp, index_of_largest, index;
    for (int limit = ROWS-1; limit > 0; limit--) {
        index_of_largest = 0;
        for (index = 1; index <= limit; index++) {
            if (a[index][1] < a[index_of_largest][1]) {
                index_of_largest = index;
            }
        }
        if (limit != index_of_largest) {
            for (int i = 0; i < COLS; i++) {
                temp = a[limit][i];
                a[limit][i] = a[index_of_largest][i];
                a[index_of_largest][i] = temp;
            }
        }
    }
}

void shellSort() {
    int temp;
    for (int gap = ROWS/2; gap >= 1; gap = gap/2) {
        for (int i = gap; i < ROWS; i++) {
            for (int j = i; j >= gap && a[j-gap][2] > a[j][2]; j = j-gap) {
                for (int i = 0; i < COLS; i++) {
                    temp = a[j-gap][i];
                    a[j-gap][i] = a[j][i];
                    a[j][i] = temp;
                }
            }
        }
    }
}

void insertionSort() {
    int temp;
    for (int i = 1; i < COLS; i++) {
        for (int j = i; j > 0 && a[4][j] < a[4][j-1]; j--) {
            for (int i = 0; i < ROWS; i++) {
                temp = a[i][j];
                a[i][j] = a[i][j-1];
                a[i][j-1] = temp;
            }
        }
    }
}

void binarySearch(int key) {
    int high = COLS-1, low = 0, mid = 0;
    bool found = false;
    while (high >= low && !found) {
        mid = (high + low) / 2;
        if (key > a[4][mid]) {
            low = mid + 1;
        } else if (key < a[4][mid]) {
            high = mid - 1;
        } else {
            found = true;
        }
    }
    if (found) {
        cout << "+------+" << endl;
        for (int i = 0; i < ROWS; i++) {
            cout << '|' << setw(5) << a[i][mid] << ' ' << '|' << endl;
            cout << "+------+" << endl;
        }
    }
}

int main() {
    int input;

    initializeArray();
    cout << "Original array:" << endl;
    displayArray();

    bubbleSort();
    cout << "Array after bubble sort:" << endl;
    displayArray();

    initializeArray();
    selectionSort();
    cout << "Array after selection sort:" << endl;
    displayArray();

    initializeArray();
    shellSort();
    cout << "Array after shell sort:" << endl;
    displayArray();

    initializeArray();
    insertionSort();
    cout << "Array after insertion sort:" << endl;
    displayArray();

    cout << "Please enter a number to search for in the last row: ";
    cin >> input;
    binarySearch(input);

    return 0;
}
