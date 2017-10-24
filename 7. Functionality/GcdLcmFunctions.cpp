#include <iostream>
#include <stdlib.h>

using namespace std;


int greatestCommonDenominator(const int a, const int b) {
	if (a < 1 || b < 1) {
		return -1;
	}
	int tmp;
	int gcd = a;
	int s = b;
	while (s != 0)
	{
		tmp = s;
		s = gcd % s;
		gcd = tmp;
	}
	return gcd;
}

int leastCommonMultiple(const int a, const int b) {
	int lcm;
	if (a < 1 || b < 1) {
		return -1;
	}
	else if (a / greatestCommonDenominator(a, b) > 2147483647 / b) {
		return -2;
	}

	lcm = (a / greatestCommonDenominator(a, b) * b);
	return lcm;
}

int main(const int argc, const char* const argv[]) {

	if (argc < 3) {
		cerr << "Error: Usage: " << argv[0] << "<num1> <num2>; exiting" << endl;
		return -1;
	}

	int gcd = greatestCommonDenominator(atoi(argv[1]), atoi(argv[2]));
	if (gcd < 0)
		cerr << "Unable to compute GCD(" << argv[1] << "," << argv[2] << ")" << endl;
	else
		cout << "GCD(" << argv[1] << "," << argv[2] << ") = " << gcd << endl;

	int lcm = leastCommonMultiple(atoi(argv[1]), atoi(argv[2]));
	if (lcm < 0)
		cerr << "Unable to compute LCM(" << argv[1] << "," << argv[2] << ")" << endl;
	else
		cout << "LCM(" << argv[1] << "," << argv[2] << ") = " << lcm << endl;


	return 0;
}
