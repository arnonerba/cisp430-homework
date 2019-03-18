//
//  Author: Arnon Erba
//  Assignment: Group 2 SplitMerge
//  Objective: Read names from a file into a linked list. Split
//  and merge the linked list.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
    string name;
    node *next;
};

node *ReadFile(ifstream &inputFile) {
    node *head = nullptr;
    string line;
    while (inputFile >> line) {
        node *nn = new node;
        nn->name = line;
        nn->next = head;
        head = nn;
    }
    return head;
}

void Traverse(node *head) {
    while (head) {
        cout << head->name << endl;
        head = head->next;
    }
}

int GetListSize(node *head) {
    int length = 0;
    while (head) {
        length++;
        head = head->next;
    }
    return length;
}

node *Split(node *list1) {
    node *list2 = nullptr;
    if (list1) {
        node *temp = list1;
        for (int i = 1; i < GetListSize(list1)/2; i++) {
            temp = temp->next;
        }
        list2 = temp->next;
        temp->next = nullptr;
    }
    return list2;
}

void Merge(node *&list1, node *&list2) {
    if (list1) {
        node *temp = list1;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = list2;
    } else {
        list1 = list2;
    }
}

void SplitMerge(node *&myList1) {
    if (myList1) {
        // Split myList1 in half
        node *myList2 = Split(myList1);
        cout << "After split, myList1 is:" << endl;
        Traverse(myList1);
        cout << endl;
        cout << "After split, myList2 is:" << endl;
        Traverse(myList2);
        cout << endl;
        // Merge myList2 back together with myList1
        Merge(myList1, myList2);
        cout << "After merge, myList1 is:" << endl;
        Traverse(myList1);
    }
}

int main() {
    ifstream inputFile;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    node *myList1 = ReadFile(inputFile);
    SplitMerge(myList1);

    inputFile.close();
    return 0;
}
