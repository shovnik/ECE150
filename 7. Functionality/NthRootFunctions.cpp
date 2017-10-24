#include <iostream>
#include <stdlib.h>
#include <limits>

using namespace std;


float NthRoot(const float S, const int N, const float precision);


float NthRoot(const float S, const int N, const float precision)
{
	float nan = std::numeric_limits<float>::quiet_NaN();
	if (N < 2)
	{
		return nan;
	}
	if (precision <= 0)
	{
		return nan;
	}
	if (N % 2 == 0 && S < 0)
	{
		return nan;
	}
	if (S == 0)
	{
		return 0;
	}
	float dif;
	float s = S;
	float guess;
	if (s < 0)
	{
		s = s * (-1);
	}
	if (s > 1)
	{
		guess = s / 2;
	}
	else
	{
		guess = 1;
	}
	int i = 0;
	while (i < 1)
	{
		float y = guess;
		int j = 1;
		while (j < N)
		{
			y = y * guess;
			j += 1;
		}
		if (s > y)
		{
			dif = ((s - y) / s);
		}
		else
		{
			dif = ((y - s) / s);
		}

		if (dif <= precision)
		{
			i += 1;
			if (S < 0)
			{
				guess = guess * (-1);
			}
			return guess;
		}
		else
		{
			guess = ((float)(N - 1) / N) * guess + s / ((float)N * (y / guess));
		}
	}
}


int main(const int argc, const char* const argv[])
{

	if (argc < 4)
	{
		cerr << "Error: Usage: " << argv[0] << " <number> <root> <precision>; exiting" << endl;
		return -1;
	}

	float root = NthRoot(atof(argv[1]), atoi(argv[2]), atof(argv[3]));
	if (isNaN(root))
		cerr << "Unable to compute " << argv[2] << "th root of " << argv[1] << " with precision "
		<< argv[3] << endl;
	else
		cout << "Root(" << argv[1] << "," << argv[2] << ") = " << root << endl
		<< "(with precision " << argv[3] << ")" << endl;

	return 0;
}
