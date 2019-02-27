//
//  Author: Arnon Erba
//  Assignment: Group 4 Queues
//  Objective: Populate a queue with a list of integers
//  (both positive and negative) from a file (input.txt).
//  Write an algorithm that deletes all negative integers
//  without changing the order of the remaining elements.
//

#include <iostream>
#include <fstream>

using namespace std;

struct node {
    int data;
    node *next;
};

void enqueue(node *&front, node *&rear, int data) {
    node *nn = new node;
    nn->data = data;
    nn->next = nullptr;
    if (rear) {
        rear->next = nn;
        rear = nn;
    } else {
        front = rear = nn;
    }
}

int dequeue(node *&front, node *&rear) {
    int data = -1;
    if (front) {
        data = front->data;
        node *temp = front;
        front = front->next;
        delete temp;
        if (!front) {
            front = rear = nullptr;
        }
    }
    return data;
}

void traverse(node *front) {
    while (front) {
        cout << front->data << ' ';
        front = front->next;
    }
    cout << endl;
}

void removeNegatives(node *&front, node *&rear) {
    node *placeholder = rear;
    int temp;
    while (front != placeholder) {
        temp = dequeue(front, rear);
        if (temp >= 0) {
            enqueue(front, rear, temp);
        }
    }
    temp = dequeue(front, rear);
    if (temp >= 0) {
        enqueue(front, rear, temp);
    }
}

int main() {
    ifstream inputFile;
    node *front = nullptr, *rear = nullptr;
    int input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    while (inputFile >> input) {
        enqueue(front, rear, input);
    }

    traverse(front);
    removeNegatives(front, rear);
    traverse(front);

    inputFile.close();
    return 0;
}
