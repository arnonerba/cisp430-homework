//
//  Author: Arnon Erba
//  Assignment: Group 13 Expression Tree
//  Objective: Read a postfix expression from a file.
//  Place it in an expression tree. Evaluate the expression tree.
//  Display the expression tree in infix notation with the
//  parentheses in the correct place.
//

#include <iostream>
#include <fstream>

using namespace std;

struct BinaryTree {
    char data;
    BinaryTree *left;
    BinaryTree *right;
};

struct node {
    BinaryTree *leaf;
    node *next;
};

void push(node *&head, BinaryTree *leaf) {
    node *nn = new node;
    nn->leaf = leaf;
    if (head) {
        nn->next = head;
    } else {
        nn->next = nullptr;
    }
    head = nn;
}

BinaryTree *pop(node *&head) {
    BinaryTree *leaf = nullptr;
    if (head) {
        leaf = head->leaf;
        node *temp = head;
        head = head->next;
        delete temp;
    }
    return leaf;
}

int postOrder(BinaryTree *tree) {
    if (tree) {
        int left = postOrder(tree->left);
        int right = postOrder(tree->right);
        if (!isdigit(tree->data)) {
            switch (tree->data) {
                case '^':
                    return left ^ right;
                    break;
                case '/':
                    return left / right;
                    break;
                case '*':
                    return left * right;
                    break;
                case '+':
                    return left + right;
                    break;
                case '-':
                    return left - right;
                    break;
                default:
                    return -1;
            }
        } else {
            return tree->data - '0';
        }
    } else {
        return 0;
    }
}

void inOrder(BinaryTree *tree, bool isRoot = true) {
    if (tree) {
        if (tree->left && !isRoot) {
            cout << '(';
        }
        inOrder(tree->left, false);
        cout << tree->data;
        inOrder(tree->right, false);
        if (tree->right && !isRoot) {
            cout << ')';
        }
    }
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
        BinaryTree *temp = new BinaryTree;
        temp->data = input;
        if (isdigit(input)) {
            temp->left = nullptr;
            temp->right = nullptr;
        } else {
            BinaryTree *T1 = pop(stack);
            BinaryTree *T2 = pop(stack);
            temp->left = T2;
            temp->right = T1;
        }
        push(stack, temp);
    }

    BinaryTree *tree = pop(stack);
    cout << "Expression result: " << postOrder(tree) << endl;
    cout << "Infix notation: ";
    inOrder(tree);
    cout << endl;

    inputFile.close();
    return 0;
}
