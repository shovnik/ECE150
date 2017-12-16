#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;


void swap(float& num1, float& num2)
{
	float tmp = num1;
	num1 = num2;
	num2 = tmp;
}

void bubbleSort(int start, int end, float arr[])
{
	bool sorted = false;
	int unsortedEnd = end - 1;
	while (!sorted)
	{
		sorted = true;
		for (int currentElement = start; currentElement < unsortedEnd; currentElement++)
		{
			if (arr[currentElement] > arr[currentElement + 1])
			{
				swap(arr[currentElement], arr[currentElement + 1]);
				sorted = false;
			}
		}
		unsortedEnd--;
	}
}

int main(const int argc, const char* const argv[])
{
	float data[argc - 1];
	for (int i = 0; i < argc - 1; i++)
	{
		data[i] = atof(argv[i + 1]);
	}
	bubbleSort(0, argc - 2, data);
	for (int i = 0; i < argc - 1; i++)
	{
		cout << data[i] << " ";
	}
	return 0;
}
