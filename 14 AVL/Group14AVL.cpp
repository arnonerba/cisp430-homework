//
//  Author: Arnon Erba
//  Assignment: Group 14 AVL
//  Objective: Populate a tree via a text file (input.txt).
//  Make sure that after every insert, the tree is balanced.
//  At the end, display the tree in level format. Make sure
//  to include the height and the balance factor of every
//  node in your output. Redirect the display to an output
//  file (output.txt).
//

#include <iostream>
#include <fstream>

using namespace std;

struct AVLTree {
    int data;
    int height;
    AVLTree *left;
    AVLTree *right;
};

struct node {
    AVLTree *leaf;
    node *next;
};

struct queue {
    node *front = nullptr;
    node *rear = nullptr;
};

void enqueue(queue &queue, AVLTree *leaf) {
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

AVLTree *dequeue(queue &queue) {
    AVLTree *leaf = nullptr;
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

int max(int a, int b) {
    return (a < b) ? b : a;
}

int getHeight(AVLTree *leaf) {
    if (leaf) {
        return leaf->height;
    } else {
        return -1;
    }
}

void setHeight(AVLTree *leaf) {
    if (leaf) {
        leaf->height = max(getHeight(leaf->left), getHeight(leaf->right)) + 1;
    }
}

int getBalance(AVLTree *leaf) {
    return getHeight(leaf->left) - getHeight(leaf->right);
}

AVLTree *leftRotate(AVLTree *x) {
    AVLTree *y = x->right;
    AVLTree *z = y->left;
    y->left = x;
    x->right = z;
    setHeight(x);
    setHeight(y);
    return y;
}

AVLTree *rightRotate(AVLTree *x) {
    AVLTree *y = x->left;
    AVLTree *z = y->right;
    y->right = x;
    x->left = z;
    setHeight(x);
    setHeight(y);
    return y;
}

AVLTree *rebalance(AVLTree *leaf) {
    setHeight(leaf);
    int balance = getBalance(leaf);
    if (balance > 1) {
        // Left heavy
        if (getBalance(leaf->left) > 0) {
            // Heavy outside
            return rightRotate(leaf);
        } else {
            // Heavy inside
            leaf->left =  leftRotate(leaf->left);
            return rightRotate(leaf);
        }
    } else if (balance < -1) {
        // Right heavy
        if (getBalance(leaf->right) < 0) {
            // Heavy outside
            return leftRotate(leaf);
        } else {
            // Heavy inside
            leaf->right = rightRotate(leaf->right);
            return leftRotate(leaf);
        }
    } else {
        return leaf;
    }
}

AVLTree *insert(AVLTree *leaf, int data) {
    if (!leaf) {
        leaf = new AVLTree;
        leaf->data = data;
        leaf->left = nullptr;
        leaf->right = nullptr;
    } else if (data < leaf->data) {
        leaf->left = insert(leaf->left, data);
    } else if (data > leaf->data) {
        leaf->right = insert(leaf->right, data);
    }
    leaf = rebalance(leaf);
    return leaf;
}

void byLevel(AVLTree *tree, ofstream &outputFile) {
    queue currentLevel, nextLevel;
    enqueue(currentLevel, tree);
    while (currentLevel.front) {
        AVLTree *temp = dequeue(currentLevel);
        outputFile << temp->data << ' ' << '(' << getHeight(temp) << ',' << getBalance(temp) << ')' << ' ';
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
    AVLTree *tree = nullptr;
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

    while (inputFile >> input) {
        tree = insert(tree, input);
    }

    outputFile << "By level format (h,b):" << endl;
    byLevel(tree, outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
