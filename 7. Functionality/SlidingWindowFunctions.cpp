#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <limits>
#include <math.h>

using namespace std;

int SWMinimum(const float dataset[], const int size, const int currentSample, const int windowSize,
	float& minimum)
{
	if (size < 1 || windowSize < 1)
	{
		return -1;
	}
	else if (windowSize > size)
	{
		return 1;
	}
	float arr[size + windowSize];
	for (int i = 0; i < windowSize - 1; i++)
	{
		arr[i] = dataset[0];
	}
	for (int i = windowSize - 1; i < size + windowSize - 1; i++)
	{
		arr[i] = dataset[i - windowSize + 1];
	}
	minimum = arr[currentSample];
	for (int i = currentSample + 1; i < currentSample + windowSize; i++)
	{
		if (arr[i] < minimum)
		{
			minimum = arr[i];
		}
	}
	return 0;
}

int SWAverage(const float dataset[], const int size, const int currentSample, const int windowSize,
	float& average)
{
	if (size < 1 || windowSize < 1)
	{
		return -1;
	}
	else if (windowSize > size)
	{
		return 1;
	}
	float arr[size + windowSize];
	for (int i = 0; i < windowSize - 1; i++)
	{
		arr[i] = dataset[0];
	}
	for (int i = windowSize - 1; i < size + windowSize - 1; i++)
	{
		arr[i] = dataset[i - windowSize + 1];
	}
	float sum = 0;
	for (int i = currentSample; i < currentSample + windowSize; i++)
	{
		sum += arr[i];
	}
	average = sum / windowSize;
	return 0;
}

int SWMaximum(const float dataset[], const int size, const int currentSample, const int windowSize,
	float& maximum)
{
	if (size < 1 || windowSize < 1)
	{
		return -1;
	}
	else if (windowSize > size)
	{
		return 1;
	}
	float arr[size + windowSize];
	for (int i = 0; i < windowSize - 1; i++)
	{
		arr[i] = dataset[0];
	}
	for (int i = windowSize - 1; i < size + windowSize - 1; i++)
	{
		arr[i] = dataset[i - windowSize + 1];
	}
	maximum = arr[currentSample];
	for (int i = currentSample + 1; i < currentSample + windowSize; i++)
	{
		if (arr[i] > maximum)
		{
			maximum = arr[i];
		}
	}
	return 0;
}

int SWSmplStdDev(const float dataset[], const int size, const int currentSample,
	const int windowSize, float& smplStdDev)
{
	if (size < 1 || windowSize < 1)
	{
		return -1;
	}
	else if (windowSize > size || windowSize == 1)
	{
		return 1;
	}
	float arr[size + windowSize];
	for (int i = 0; i < windowSize - 1; i++)
	{
		arr[i] = dataset[0];
	}
	for (int i = windowSize - 1; i < size + windowSize - 1; i++)
	{
		arr[i] = dataset[i - windowSize + 1];
	}
	float tmpsum = 0;
	float sumdif = 0;
	for (int i = currentSample; i < currentSample + windowSize; i++)
	{
		tmpsum += arr[i];
	}
	float tmpavg = tmpsum / windowSize;
	for (int i = currentSample; i < currentSample + windowSize; i++)
	{
		sumdif += pow((arr[i] - tmpavg), 2);
	}
	smplStdDev = sqrt(sumdif / (windowSize - 1));
	return 0;
}

int SWMedian(const float dataset[], const int size, const int currentSample, const int windowSize,
	float& median)
{
	if (size < 1 || windowSize < 1)
	{
		return -1;
	}
	else if (windowSize > size)
	{
		return 1;
	}
	float arr[size + windowSize];
	for (int i = 0; i < windowSize - 1; i++)
	{
		arr[i] = dataset[0];
	}
	for (int i = windowSize - 1; i < size + windowSize - 1; i++)
	{
		arr[i] = dataset[i - windowSize + 1];
	}
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = currentSample; i < currentSample + windowSize - 1; i++)
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
	if (windowSize % 2 == 0)
	{
		median = (arr[currentSample + (windowSize / 2) - 1] + arr[currentSample + (windowSize / 2)])
			/ 2;
		return 0;
	}
	else
	{
		median = arr[currentSample + (windowSize - 1) / 2];
		return 0;
	}
}

int SWStats(const float dataset[], const int size, const int currentSample, const int windowSize,
	float& min, float& avg, float& max, float& smplSD, float& mdn)
{
	float errorcheck = 0;
	errorcheck += SWMinimum(dataset, size, currentSample, windowSize, min);
	errorcheck += SWAverage(dataset, size, currentSample, windowSize, avg);
	errorcheck += SWMaximum(dataset, size, currentSample, windowSize, max);
	errorcheck += SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD);
	errorcheck += SWMedian(dataset, size, currentSample, windowSize, mdn);
	if (errorcheck < 0)
	{
		return -1;
	}
	else if (errorcheck > 0)
	{
		return 1;
	}
	return 0;
}

int main(const int argc, const char* const argv[])
{
	if (argc < 2)
	{
		cerr << "Error: Unable to compute statistics because data set is empty." << endl;
	}
	else
	{
		int size = argc - 2;
		float dataset[argc - 2];
		for (int i = 0; i < size; i++)
		{
			dataset[i] = atof(argv[i + 2]);
		}
		int windowSize = atoi(argv[1]);
		int currentSample = 0;
		float min;
		float avg;
		float max;
		float smplSD;
		float mdn;

		const char s = ' '; // separator
		const int w = 12; // width per slot
		cout << "Window Size = " << windowSize << endl;
		cout << left << setw(w) << setfill(s) << "Sample";
		cout << left << setw(w) << setfill(s) << "Minimum";
		cout << left << setw(w) << setfill(s) << "Average";
		cout << left << setw(w) << setfill(s) << "Maximum";
		cout << left << setw(w) << setfill(s) << "Std Dev.";
		cout << left << setw(w) << setfill(s) << "Median";
		cout << endl;

		while (currentSample < size)
		{
			int retCode
				= SWStats(dataset, size, currentSample, windowSize, min, avg, max, smplSD, mdn);
			if (retCode >= 0)
			{
				cout << left << setw(w) << setfill(s) << currentSample;
				cout << left << setw(w) << setfill(s) << min;
				cout << left << setw(w) << setfill(s) << avg;
				cout << left << setw(w) << setfill(s) << max;
				cout << left << setw(w) << setfill(s) << smplSD;
				cout << left << setw(w) << setfill(s) << mdn;
				cout << endl;

				if (retCode > 0)
				{
					cerr << "Warning: something weird happened, but we computed stats anyway ... "
						"YMMV"
						<< endl;
				}
			}
			else
			{
				cerr << "Error: unable to compute sliding-window statistics; exiting" << endl;
				return (-1);
			}
			currentSample += 1;
		}
	}
	return 0;
}
