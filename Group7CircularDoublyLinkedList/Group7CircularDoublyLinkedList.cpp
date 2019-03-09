//
//  Author: Arnon Erba
//  Assignment: Group 7 Circular Doubly Linked List
//  Objective: Create a circular, doubly linked list from
//  a file (input.txt), containing a list of names. The
//  number of names is unknown. Prompt the user for the number
//  of nodes to delete and then delete accordingly from the list.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
    string name;
    node *next;
    node *prev;
};

void insertNode(node *&head, string name) {
    node *nn = new node;
    nn->name = name;
    if (!head) {
        nn->next = nn;
        nn->prev = nn;
    } else {
        nn->next = head;
        nn->prev = head->prev;
        head->prev->next = nn;
        head->prev = nn;
    }
    head = nn;
}

void removeNode(node *&head) {
    if (head) {
        node *temp = head;
        if (head->next == head) {
            head = nullptr;
        } else {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
        }
        delete temp;
    }
}

int main() {
    ifstream inputFile;
    node *head = nullptr;
    string line;
    int input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    while (inputFile >> line) {
        insertNode(head, line);
    }

    cout << "Enter the number of nodes to delete: ";
    cin >> input;

    while (head && input > 0) {
        removeNode(head);
        input--;
    }

    while (head) {
        cout << head->name << endl;
        removeNode(head);
    }

    inputFile.close();
    return 0;
}
