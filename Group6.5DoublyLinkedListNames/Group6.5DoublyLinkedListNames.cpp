//
//  Author: Arnon Erba
//  Assignment: Group 6.5 Doubly Linked List (Names)
//  Objective: Write a program that reads a list of students
//  (first names only) from a file. It is possible for the names
//  to be in unsorted order in the file but they have to be placed
//  in sorted order within the linked list. The program should use
//  a doubly linked list.
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

void addName(node *&head, node*&tail, string name) {
    node *nn = new node;
    nn->name = name;
    if (!head) {
        nn->next = nullptr;
        nn->prev = nullptr;
        head = tail = nn;
    } else if (name < head->name) {
        nn->next = head;
        nn->prev = nullptr;
        head->prev = nn;
        head = nn;
    } else if (name > tail->name) {
        nn->next = nullptr;
        nn->prev = tail;
        tail->next = nn;
        tail = nn;
    } else {
        node *temp = head;
        while (temp && name > temp->name) {
            temp = temp->next;
        }
        nn->next = temp;
        nn->prev = temp->prev;
        temp->prev->next = nn;
        temp->prev = nn;
    }
}

void deleteName(node *&head, node*&tail, string name) {
    node *temp = head;
    bool found = false;
    while (temp && !found) {
        if (temp->name == name) {
            found = true;
        } else {
            temp = temp->next;
        }
    }
    if (found) {
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

void flushList(node *&head, node *&tail, ofstream &outputFile) {
    while (head) {
        outputFile << head->name << endl;
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

void traverseAscending(node *head) {
    while (head) {
        cout << head->name << endl;
        head = head->next;
    }
}

void traverseDescending(node *tail) {
    while (tail) {
        cout << tail->name << endl;
        tail = tail->prev;
    }
}

int main() {
    ifstream inputFile;
    ofstream outputFile;
    node *head = nullptr, *tail = nullptr;
    string input;

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

    while (inputFile >> input) {
        if (input == "delete") {
            inputFile >> input;
            deleteName(head, tail, input);
        } else {
            addName(head, tail, input);
        }
    }

    cout << "Ascending order:" << endl;
    traverseAscending(head);
    cout << endl;

    cout << "Descending order:" << endl;
    traverseDescending(tail);
    cout << endl;

    flushList(head, tail, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
