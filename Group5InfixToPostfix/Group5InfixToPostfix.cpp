//
//  Author: Arnon Erba
//  Assignment: Group 5 Infix To Postfix
//  Objective: Read an infix expression from an input file
//  and convert to postfix. Instead of displaying directly
//  on the screen, first place in a queue, and then display
//  the contents of the queue on the screen.
//

#include <iostream>
#include <fstream>

using namespace std;

struct node {
    char data;
    node *next;
};

void push(node *&head, char data) {
    node *nn = new node;
    nn->data = data;
    if (head) {
        nn->next = head;
    } else {
        nn->next = nullptr;
    }
    head = nn;
}

char pop(node *&head) {
    char data = '\0';
    if (head) {
        data = head->data;
        node *temp = head;
        head = head->next;
        delete temp;
    }
    return data;
}

void enqueue(node *&front, node *&rear, char data) {
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

char dequeue(node *&front, node *&rear) {
    char data = '\0';
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

int getPrecedence(char input) {
    int precedence;
    switch (input) {
        case '^':
            precedence = 5;
            break;
        case '/':
            precedence = 4;
            break;
        case '*':
            precedence = 4;
            break;
        case '+':
            precedence = 3;
            break;
        case '-':
            precedence = 3;
            break;
        case '=':
            precedence = 2;
            break;
        default:
            precedence = 1;
    }
    return precedence;
}

int main() {
    ifstream inputFile;
    node *stack = nullptr, *front = nullptr, *rear = nullptr;
    char input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    while (inputFile >> input) {
        if (isdigit(input) || isalpha(input)) {
            enqueue(front, rear, input);
        } else {
            if (!stack) {
                push(stack, input);
            } else {
                if (input == '(') {
                    push(stack, input);
                } else if (input == ')') {
                    while (stack->data != '(') {
                        enqueue(front, rear, pop(stack));
                    }
                    pop(stack);
                } else if (getPrecedence(input) > getPrecedence(stack->data)) {
                    push(stack, input);
                } else {
                    while ((stack) && (getPrecedence(input) <= getPrecedence(stack->data))) {
                        enqueue(front, rear, pop(stack));
                    }
                    push(stack, input);
                }
            }
        }
    }
    while (stack) {
        enqueue(front, rear, pop(stack));
    }

    traverse(front);

    inputFile.close();
    return 0;
}
