#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
	if (argc < 3)
	{
		cerr << "Error: Unable to compute GCD and/or LCM because there is an insufficient amount "
			"of arguments."
			<< endl;
	}
	else
	{
		if (argc > 3)
		{
			cerr << "Warning: Expecting two command-line arguments; received " << (argc - 1)
				<< "; ignoring extraneous arguments." << endl;
		}
		int a = atoi(argv[1]);
		int b = atoi(argv[2]);
		if (a < 1 || b < 1)
		{
			cerr << "Error: Unable to compute GCD and/or LCM because a negative number or zera was "
				"used as input."
				<< endl;
		}
		else
		{
			int gcd = a;
			int s = b;
			int t;
			while (s != 0)
			{
				t = s;
				s = gcd % s;
				gcd = t;
			}
			int lcm = (a / gcd) * b;

			cout << "GCD (" << a << "," << b << ") = " << gcd << endl;
			cout << "LCM (" << a << "," << b << ") = " << lcm << endl;
		}
	}
}
