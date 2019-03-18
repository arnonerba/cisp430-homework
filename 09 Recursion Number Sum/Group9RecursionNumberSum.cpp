//
//  Author: Arnon Erba
//  Assignment: Group 9 Recursion Number Sum
//  Objective: Write a recursive function that sums
//  the individual digits in a number.
//

#include <iostream>

using namespace std;

int recursionSum(int input) {
    if (input == 0) {
        return 0;
    } else {
        return (input % 10) + recursionSum(input / 10);
    }
}

int main() {
    int input;
    
    cout << "Enter a number: ";
    cin >> input;
    
    cout << recursionSum(input) << endl;
    
    return 0;
}
