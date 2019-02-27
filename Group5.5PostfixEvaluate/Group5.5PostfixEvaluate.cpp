//
//  Author: Arnon Erba
//  Assignment: Group 5.5 Postfix Evaluate
//  Objective: Read a postfix expression from an input file.
//  Evaluate the postfix format and display the results.
//  No error checking is necessary.
//

#include <iostream>
#include <fstream>

using namespace std;

struct node {
    int data;
    node *next;
};

void push(node *&head, int data) {
    node *nn = new node;
    nn->data = data;
    if (head) {
        nn->next = head;
    } else {
        nn->next = nullptr;
    }
    head = nn;
}

int pop(node *&head) {
    int data = -1;
    if (head) {
        data = head->data;
        node *temp = head;
        head = head->next;
        delete temp;
    }
    return data;
}

int main() {
    ifstream inputFile;
    node *stack = nullptr;
    char input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    while (inputFile >> input) {
        if (isdigit(input)) {
            push(stack, input - '0');
        } else if (input == '=') {
            cout << pop(stack) << endl;
        } else {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (input) {
                case '^':
                    push(stack, operand1 ^ operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                default:
                    push(stack, -1);
            }
        }
    }

    inputFile.close();
    return 0;
}
