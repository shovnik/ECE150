/////////////////////////////////////////////////////////////////////
//
// 1-average
// Input: two integers, read from cin, not error checked
// Output: integer average of the two inputs, displayed on cout
//

#include <iostream>

using namespace std;

int main() {
    int x;
    int y;
    int average;

    cout << "Enter an integer: ";
    cin >> x;

    cout << "Enter a second integer: ";
    cin >> y;

    average = (x+y)/2;

    cout << "Average of " << x << " and " << y << " is " << average << endl;

    return 0;
}
