//
//  Author: Arnon Erba
//  Assignment: Group 12 Delete Tree
//  Objective: Populate a binary search tree from an input file
//  that contains a list of numbers. The file can also contain
//  the keyword delete followed by a number. Search for a node
//  within the tree for that number and delete it. If the number
//  is not found, insert the node.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct BinaryTree {
    int data;
    BinaryTree *left;
    BinaryTree *right;
};

struct node {
    BinaryTree *leaf;
    node *next;
};

struct queue {
    node *front = nullptr;
    node *rear = nullptr;
};

void enqueue(queue &queue, BinaryTree *leaf) {
    node *nn = new node;
    nn->leaf = leaf;
    nn->next = nullptr;
    if (queue.rear) {
        queue.rear->next = nn;
        queue.rear = nn;
    } else {
        queue.front = queue.rear = nn;
    }
}

BinaryTree *dequeue(queue &queue) {
    BinaryTree *leaf = nullptr;
    if (queue.front) {
        leaf = queue.front->leaf;
        node *temp = queue.front;
        queue.front = queue.front->next;
        delete temp;
        if (!queue.front) {
            queue.front = queue.rear = nullptr;
        }
    }
    return leaf;
}

BinaryTree *insert(BinaryTree *leaf, int data) {
    if (!leaf) {
        leaf = new BinaryTree;
        leaf->data = data;
        leaf->left = nullptr;
        leaf->right = nullptr;
    } else if (data < leaf->data) {
        leaf->left = insert(leaf->left, data);
    } else if (data > leaf->data) {
        leaf->right = insert(leaf->right, data);
    }
    return leaf;
}

BinaryTree *remove(BinaryTree *leaf, int data) {
    if (!leaf) {
        leaf = nullptr;
    } else if (data == leaf->data) {
        if (!leaf->left && !leaf->right) {
            delete leaf;
            leaf = nullptr;
        } else if (!leaf->left || !leaf->right) {
            BinaryTree *temp;
            if (leaf->left) {
                temp = leaf->left;
            } else {
                temp = leaf->right;
            }
            delete leaf;
            leaf = temp;
        } else {
            BinaryTree *temp = leaf->right;
            while (temp->left) {
                temp = temp->left;
            }
            leaf->data = temp->data;
            leaf->right = remove(leaf->right, leaf->data);
        }
    } else if (data < leaf->data) {
        leaf->left = remove(leaf->left, data);
    } else if (data > leaf->data) {
        leaf->right = remove(leaf->right, data);
    }
    return leaf;
}

bool search(BinaryTree *leaf, int data) {
    bool found = false;
    if (leaf) {
        if (data == leaf->data) {
            found = true;
        } else if (data < leaf->data) {
            found = search(leaf->left, data);
        } else {
            found = search(leaf->right, data);
        }
    }
    return found;
}

void preOrder(BinaryTree *tree, ofstream &outputFile) {
    if (tree) {
        outputFile << tree->data << ' ';
        preOrder(tree->left, outputFile);
        preOrder(tree->right, outputFile);
    }
}

void inOrder(BinaryTree *tree, ofstream &outputFile) {
    if (tree) {
        inOrder(tree->left, outputFile);
        outputFile << tree->data << ' ';
        inOrder(tree->right, outputFile);
    }
}

void postOrder(BinaryTree *tree, ofstream &outputFile) {
    if (tree) {
        postOrder(tree->left, outputFile);
        postOrder(tree->right, outputFile);
        outputFile << tree->data << ' ';
    }
}

void byLevel(BinaryTree *tree, ofstream &outputFile) {
    queue currentLevel, nextLevel;
    enqueue(currentLevel, tree);
    while (currentLevel.front) {
        BinaryTree *temp = dequeue(currentLevel);
        outputFile << temp->data << ' ';
        if (temp->left) {
            enqueue(nextLevel, temp->left);
        }
        if (temp->right) {
            enqueue(nextLevel, temp->right);
        }
        if (currentLevel.front == nullptr) {
            currentLevel = nextLevel;
            nextLevel.front = nextLevel.rear = nullptr;
            outputFile << endl;
        }
    }
}

int main() {
    ifstream inputFile;
    ofstream outputFile;
    BinaryTree *tree = nullptr;
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
            if (search(tree, stoi(input))) {
                tree = remove(tree, stoi(input));
            } else {
                tree = insert(tree, stoi(input));
            }
        } else {
            if (!search(tree, stoi(input))) {
                tree = insert(tree, stoi(input));
            }
        }
    }

    outputFile << "Preorder format:" << endl;
    preOrder(tree, outputFile);
    outputFile << endl << endl;

    outputFile << "Inorder format:" << endl;
    inOrder(tree, outputFile);
    outputFile << endl << endl;

    outputFile << "Postorder format:" << endl;
    postOrder(tree, outputFile);
    outputFile << endl << endl;

    outputFile << "By level format:" << endl;
    byLevel(tree, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
