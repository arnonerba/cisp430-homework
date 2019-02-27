//
//  Author: Arnon Erba
//  Assignment: Group 6 Doubly Linked List
//  Objective: Create a doubly linked list from a file (input.txt).
//  The number of items is unknown.
//  (Delete from head) Prompt the user for a node number. Starting
//  from the head, moving forward, go to the node and delete it.
//  (Delete from tail) Prompt the user for another node number.
//  Starting from the tail, moving backward, go to the node and delete it.
//  Write the contents of the modified list into a file (output.txt).
//

#include <iostream>
#include <fstream>

using namespace std;

struct node {
    int data;
    node *next;
    node *prev;
};

void createList(node *&head, node *&tail, ifstream &inputFile) {
    int temp;
    while (inputFile >> temp) {
        node *nn = new node;
        nn->data = temp;
        nn->next = nullptr;
        if (tail) {
            nn->prev = tail;
            tail->next = nn;
            tail = nn;
        } else {
            nn->prev = nullptr;
            head = tail = nn;
        }
    }
}

void flushList(node *&head, node *&tail, ofstream &outputFile) {
    while (head) {
        outputFile << head->data << endl;
        node *temp = head;
        if (head->next) {
            head->next->prev = nullptr;
            head = head->next;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }
}

void deleteFromHead(node *&head, node *&tail, int pos) {
    if (head && pos > 0) {
        node *temp = head;
        for (int i = 1; i < pos && temp->next; i++) {
            temp = temp->next;
        }
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;
        }
        delete temp;
    }
}

void deleteFromTail(node *&head, node *&tail, int pos) {
    if (tail && pos > 0) {
        node *temp = tail;
        for (int i =1; i < pos && temp->prev; i++) {
            temp = temp->prev;
        }
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;
        }
        delete temp;
    }
}

int main() {
    ifstream inputFile;
    ofstream outputFile;
    node *head = nullptr, *tail = nullptr;
    int input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }
    outputFile.open("output.txt");
    if (!outputFile) {
        cout << "Failed to open output file." << endl;
        return 1;
    }

    createList(head, tail, inputFile);

    cout << "Which item do you want to delete from the beginning? ";
    cin >> input;
    deleteFromHead(head, tail, input);
    cout << "Which item do you want to delete from the end? ";
    cin >> input;
    deleteFromTail(head, tail, input);

    flushList(head, tail, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
