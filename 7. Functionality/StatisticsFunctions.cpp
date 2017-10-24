#include <iostream>
#include <stdlib.h>
#include <limits>
#include <math.h>

using namespace std;

float minimum(const float dataset[], const int size)
{
	if (size < 1)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
	float tmpmin = dataset[0];
	for (int i = 1; i < size; i++)
	{
		if (dataset[i] < tmpmin)
			tmpmin = dataset[i];
	}
	return tmpmin;
}

float average(const float dataset[], const int size)
{
	if (size < 1)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
	float tmpsum = 0;
	for (int i = 0; i < size; i++)
	{
		tmpsum += dataset[i];
	}
	float tmpavg = tmpsum / size;
	return tmpavg;
}

float maximum(const float dataset[], const int size)
{
	if (size < 1)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
	float tmpmax = dataset[0];
	for (int i = 1; i < size; i++)
	{
		if (dataset[i] > tmpmax)
			tmpmax = dataset[i];
	}
	return tmpmax;
}

float popStdDev(const float dataset[], const int size)
{
	if (size < 1)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
	float tmpsumdif = 0;
	for (int i = 0; i < size; i++)
	{
		tmpsumdif += pow((dataset[i] - average(dataset, size)), 2);
	}
	float tmppsd = sqrt(tmpsumdif / size);
	return tmppsd;
}

float smplStdDev(const float dataset[], const int size)
{
	if (size < 2)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}
	float tmpsumdif = 0;
	for (int i = 0; i < size; i++)
	{
		tmpsumdif += pow((dataset[i] - average(dataset, size)), 2);
	}
	float tmpssd = sqrt(tmpsumdif / (size - 1));
	return tmpssd;
}

float median(const float dataset[], const int size)
{
	float arr[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = dataset[i];
	}
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < (size - 1); i++)
		{
			if (arr[i] > arr[i + 1])
			{
				float tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = false;
			}
		}
	}
	float tmpmdn;
	if (size % 2 == 0)
	{
		tmpmdn = (arr[(size / 2) - 1] + arr[size / 2]) / 2;
		return tmpmdn;
	}
	else
	{
		tmpmdn = arr[((size - 1) / 2)];
		return tmpmdn;
	}
}

bool statistics(const float dataset[], const int size, float& min, float& avg, float& max,
	float& popSD, float& smplSD, float& mdn)
{
	min = minimum(dataset, size);
	avg = average(dataset, size);
	max = maximum(dataset, size);
	popSD = popStdDev(dataset, size);
	smplSD = smplStdDev(dataset, size);
	mdn = median(dataset, size);

	if (min != min || avg != avg || max != max || popSD != popSD || smplSD != smplSD || mdn != mdn)
	{
		return false;
	}
	return true;
}


int main(const int argc, const char* const argv[])
{
	if (argc < 2)
	{
		cerr << "Error: Unable to compute statistics because data set is empty." << endl;
	}
	else
	{
		int size = argc - 1;
		float dataset[argc - 1];
		for (int i = 0; i < size; i++)
		{
			dataset[i] = atof(argv[i + 1]);
		}
		float min;
		float avg;
		float max;
		float popStDev;
		float smplStDev;
		float median;

		if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, median))
		{
			cout << "Minimum: " << min << endl
				<< "Average: " << avg << endl
				<< "Median:  " << median << endl
				<< "Maximum: " << max << endl
				<< "Population Standard Deviation: " << popStDev << endl
				<< "Sample Standard Deviation:     " << smplStDev << endl;
		}
		else
			cout << "Error: unable to compute statistics" << endl;
	}
	return 0;
}
