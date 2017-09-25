/////////////////////////////////////////////////////////////////////
//
// 1-fibonacci
// Input: one integers, read from cin, rejected if less than 0 but
//        not otherwise checked
// Output: fibonacci(input number) provided input is less than 47
//



#include <iostream>

using namespace std;

int main() {
    int n;

    cout << "Enter a non-negative integer: ";
    cin >> n;

    if (n < 0) {
	cout << "NON-negative #$@#$^@" << endl;
	exit(-1);
    }

    if(n == 0) {
    	cout << "Fibonacci(0) = 0" << endl;
	return 0;
    }

    if(n == 1) {
    	cout << "Fibonacci(1) = 1" << endl;
	return 0;
    }

    int k;
    k = 1;

    long long Fkminus1, Fk;

    Fkminus1 = 0;
    Fk = 1;

    while(k < n) {
	k = k + 1;

	long long oldFk;
	long long oldFkminus1;

	oldFk = Fk;
	oldFkminus1 = Fkminus1;

	Fk = oldFk + oldFkminus1;
	if (Fk < 0) { 			// Ooops, we overflowed
		cout << "Input " << n << " is too big to handle\n";
		exit(+1);
	}
	Fkminus1 = oldFk;
    }

    cout << "Fibonacci(" << n << ") = " << Fk << endl;

    return 0;
}
