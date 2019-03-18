//
//  Author: Arnon Erba
//  Assignment: Group 10 Recursion Commas
//  Objective: Write a recursive function that inserts
//  commas into the appropriate places while displaying
//  a large number.
//

#include <iostream>
#include <iomanip>

using namespace std;

void recursionCommas(int input) {
    if (input < 1000) {
        cout << input;
    } else {
        recursionCommas(input / 1000);
        cout << ',' << setw(3) << setfill('0') << input % 1000;
    }
}

int main() {
    int input;
    
    cout << "Enter a number: ";
    cin >> input;
    
    recursionCommas(input);
    cout << endl;
    
    return 0;
}
