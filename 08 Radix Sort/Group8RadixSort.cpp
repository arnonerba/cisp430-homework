//
//  Author: Arnon Erba
//  Assignment: Group 8 Radix Sort
//  Objective: Sort an array of numbers in ascending
//  and descending order using radix sort.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct node {
    int data;
    node *next;
};

struct queue {
    node *front = nullptr;
    node *rear = nullptr;
};

void generateArray(int array[], int size) {
    srand(static_cast<int>(time(nullptr)));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

void copyArray(int destination[], int source[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void reverseArray(int array[], int size) {
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = array[i];
        array[i] = array[(size - 1) - i];
        array[(size - 1) - i] = temp;
    }
}

void displayArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

void enqueue(queue &queue, int data) {
    node *nn = new node;
    nn->data = data;
    nn->next = nullptr;
    if (queue.rear) {
        queue.rear->next = nn;
        queue.rear = nn;
    } else {
        queue.front = queue.rear = nn;
    }
}

int dequeue(queue &queue) {
    int data = -1;
    if (queue.front) {
        data = queue.front->data;
        node *temp = queue.front;
        queue.front = queue.front->next;
        delete temp;
        if (!queue.front) {
            queue.front = queue.rear = nullptr;
        }
    }
    return data;
}

int getMaxDigits(int array[], int size) {
    int max = array[0];
    int maxDigits = 0;
    for (int i = 1; i < size; i++) {
        if (max < array[i]) {
            max = array[i];
        }
    }
    while (max > 0) {
        maxDigits++;
        max /= 10;
    }
    return maxDigits;
}

void radixSort(int array[], int size) {
    queue queues[10];
    int divisor;
    int maxDigits = getMaxDigits(array, size);
    for (int mod = 10; mod <= pow(10, maxDigits); mod *= 10) {
        divisor = mod / 10;
        for (int i = 0; i < size; i++) {
            enqueue(queues[(array[i] % mod) / divisor], array[i]);
        }
        int index = 0;
        for (int i = 0; i < 10; i++) {
            while(queues[i].front) {
                array[index] = dequeue(queues[i]);
                index++;
            }
        }
    }
}

void radixSortReverse(int array[], int size) {
    radixSort(array, size);
    reverseArray(array, size);
}

int main() {
    int size = 15;
    int originalArray[size];
    int tempArray[size];

    generateArray(originalArray, size);
    cout << "Original array:" << endl;
    displayArray(originalArray, size);
    cout << endl;

    copyArray(tempArray, originalArray, size);
    radixSort(tempArray, size);
    cout << "Sorted array:" << endl;
    displayArray(tempArray, size);
    cout << endl;

    copyArray(tempArray, originalArray, size);
    radixSortReverse(tempArray, size);
    cout << "Reverse sorted array:" << endl;
    displayArray(tempArray, size);
    cout << endl;

    return 0;
}
