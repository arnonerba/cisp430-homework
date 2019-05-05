//
//  Author: Arnon Erba
//  Assignment: Group 11 Quicksort
//  Objective: Modify the quicksort algorithm such that
//  it uses the last item as the pivot instead of the first.
//  Also, sort in descending order, instead of ascending order.
//

#include <iostream>
#include <fstream>

using namespace std;

void displayArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

int partition(int array[], int first, int last) {
    int pivot = last, lower = first, upper = last - 1;
    while (lower <= upper) {
        while (array[lower] >= array[pivot] && lower <= upper) {
            lower++;
        }
        if (lower > upper) {
            break;
        }
        swap(array[lower], array[pivot]);
        pivot = lower;
        lower++;

        while (array[upper] <= array[pivot] && upper >= lower) {
            upper--;
        }
        if (upper < lower) {
            break;
        }
        swap(array[upper], array[pivot]);
        pivot = upper;
        upper--;
    }
    return pivot;
}

void quickSort(int array[], int start, int end) {
    int pIndex;
    if (start >= end) {
        return;
    }
    pIndex = partition(array, start, end);
    quickSort(array, start, pIndex - 1);
    quickSort(array, pIndex + 1, end);
}

int main() {
    ifstream inputFile;
    int size = 10;
    int array[size];
    int input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (inputFile >> input) {
            array[i] = input;
        } else {
            array[i] = 0;
        }
    }

    quickSort(array, 0, size - 1);
    displayArray(array, size);

    inputFile.close();
    return 0;
}
