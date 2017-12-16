#include <iostream>
#include <stdlib.h>


using namespace std;


void swap(float& num1, float& num2)
{
	float tmp = num1;
	num1 = num2;
	num2 = tmp;
}


void insertionSort(int start, int end, float arr[])
{
	int nextInsertedElement = start + 1;
	int currentElement;
	while (nextInsertedElement < end)
	{
		currentElement = nextInsertedElement;
		while (currentElement > 0 && arr[currentElement] < arr[currentElement - 1])
		{
			swap(arr[currentElement], arr[currentElement - 1]);
			currentElement--;
		}
		nextInsertedElement++;
	}
}


int main(const int argc, const char* const argv[])
{
	float data[argc - 1];
	for (int i = 0; i < argc - 1; i++)
	{
		data[i] = atof(argv[i + 1]);
	}
	insertionSort(0, argc - 2, data);
	for (int i = 0; i < argc - 1; i++)
	{
		cout << data[i] << " ";
	}
	return 0;
}
