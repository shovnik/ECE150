#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


void swap(float& num1, float& num2)
{
	float tmp = num1;
	num1 = num2;
	num2 = tmp;
}


int partition(int start, int end, float arr[])
{
	float pivot = arr[end];
	int split = start;
	for (int currentElement = start; currentElement < end; currentElement++)
	{
		if (arr[currentElement] <= pivot)
		{
			swap(arr[split], arr[currentElement]);
			split++;
		}
	}
	swap(arr[end], arr[split]);
	return split;
}


void quickSort(int start, int end, float arr[])
{
	if (start < end)
	{
		int split = partition(start, end, arr);
		quickSort(start, split - 1, arr);
		quickSort(split, end, arr);
	}
	else
	{
		return;
	}
}


int main(const int argc, const char* argv[])
{
	float data[argc - 1];
	for (int i = 0; i < argc - 1; i++)
	{
		data[i] = atof(argv[i + 1]);
	}
	quickSort(0, argc - 2, data);
	for (int i = 0; i < argc - 1; i++)
	{
		cout << data[i] << " ";
	}
	return 0;
}
