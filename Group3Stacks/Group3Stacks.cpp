//
//  Author: Arnon Erba
//  Assignment: Group 3 Stacks
//  Objective: Write a program that takes a positive integer from
//  the user and converts it into its proper binary and hexadecimal
//  representation using a LIFO structure.
//

#include <iostream>

using namespace std;

struct node {
    int digit;
    node* next;
};

void push(node *&head, int digit) {
    node *nn = new node;
    nn->digit = digit;
    if (head) {
        nn->next = head;
    } else {
        nn->next = nullptr;
    }
    head = nn;
}

void pop(node *&head) {
    if (head) {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

void displayStack(node *&head) {
    while (head) {
        switch (head->digit) {
            case 10:
                cout << 'A';
                break;
            case 11:
                cout << 'B';
                break;
            case 12:
                cout << 'C';
                break;
            case 13:
                cout << 'D';
                break;
            case 14:
                cout << 'E';
                break;
            case 15:
                cout << 'F';
                break;
            default:
                cout << head->digit;
        }
        pop(head);
    }
    cout << endl;
}

node *toBinary(int number) {
    node *newStack = nullptr;
    do {
        push(newStack, number % 2);
        number = number / 2;
    } while (number > 0);
    return newStack;
}

node *toHex(int number) {
    node *newStack = nullptr;
    do {
        push(newStack, number % 16);
        number = number / 16;
    } while (number > 0);
    return newStack;
}

int main() {
    int input;

    cout << "Enter a number to convert to binary and hex: ";
    cin >> input;

    node *binary = toBinary(input);
    node *hex = toHex(input);

    std::cout << input << " in binary is ";
    displayStack(binary);
    std::cout << input << " in hex is ";
    displayStack(hex);

    return 0;
}
