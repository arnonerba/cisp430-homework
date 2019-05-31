//
//  Author: Arnon Erba
//  Assignment: Group 16 Tree Array
//  Objective: Given a list of numbers in sorted order,
//  create a binary search tree. Insert the contents of
//  the binary search tree into an unsorted array. Using
//  the unsorted array, reconstruct the binary search tree.
//  Display the binary search tree in in-order format.
//

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct BinaryTree {
    int data;
    BinaryTree *left;
    BinaryTree *right;
};

int maxDepth(BinaryTree *tree) {
    if (tree) {
        int leftDepth = maxDepth(tree->left);
        int rightDepth = maxDepth(tree->right);
        return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
    } else {
        return -1;
    }
}

BinaryTree *sortedToTree(int array[], int start, int end) {
    int mid = (start + end) / 2;
    if (start > end) {
        return nullptr;
    } else {
        BinaryTree *leaf = new BinaryTree;
        leaf->data = array[mid];
        leaf->left = sortedToTree(array, start, mid - 1);
        leaf->right = sortedToTree(array, mid + 1, end);
        return leaf;
    }
}

void treeToUnsorted(BinaryTree *tree, int array[], int size, int i) {
    if (i < size) {
        if (tree) {
            array[i] = tree->data;
            treeToUnsorted(tree->left, array, size, (2 * i) + 1);
            treeToUnsorted(tree->right, array, size, (2 * i) + 2);
            delete tree;
        } else {
            array[i] = 0;
        }
    }
}

BinaryTree *unsortedToTree(int array[], int size, int i) {
    BinaryTree *leaf;
    if (array[i] != 0 && i < size) {
        leaf = new BinaryTree;
        leaf->data = array[i];
        leaf->left = unsortedToTree(array, size, (2 * i) + 1);
        leaf->right = unsortedToTree(array, size, (2 * i) + 2);
    } else {
        leaf = nullptr;
    }
    return leaf;
}

void inOrder(BinaryTree *tree) {
    if (tree) {
        inOrder(tree->left);
        cout << tree->data << ' ';
        inOrder(tree->right);
    }
}

void displayArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

int main() {
    ifstream inputFile;
    int arraySize = 6;
    int sorted[arraySize];
    BinaryTree *tree = nullptr;
    int input;

    inputFile.open("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    for (int i = 0; i < arraySize; i++) {
        if (inputFile >> input) {
            sorted[i] = input;
        } else {
            cout << "Input file too small." << endl;
            return 1;
        }
    }

    tree = sortedToTree(sorted, 0, arraySize - 1);
    cout << "Original tree in sorted order:" << endl;
    inOrder(tree);
    cout << endl;

    int treeSize = pow(2, maxDepth(tree) + 1) - 1;
    int unsorted[treeSize];

    treeToUnsorted(tree, unsorted, treeSize, 0);
    cout << "Tree expressed as unsorted array:" << endl;
    displayArray(unsorted, treeSize);

    tree = unsortedToTree(unsorted, treeSize, 0);
    cout << "Recreated tree in sorted order:" << endl;
    inOrder(tree);
    cout << endl;

    inputFile.close();
    return 0;
}
