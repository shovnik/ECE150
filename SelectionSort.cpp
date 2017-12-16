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


void selectionSort(int start, int end, float arr[])
{
	int nextSortedElement = start;
	while (nextSortedElement < end)
	{
		float minimum = arr[nextSortedElement];
		int selectedElement = nextSortedElement;
		for (int currentElement = nextSortedElement + 1; currentElement <= end; currentElement++)
		{
			if (arr[currentElement] < minimum)
			{
				minimum = arr[currentElement];
				selectedElement = currentElement;
			}
		}
		swap(arr[selectedElement], arr[nextSortedElement]);
		nextSortedElement++;
	}
}


int main(const int argc, const char* const argv[])
{
	float data[argc - 1];
	for (int i = 0; i < argc - 1; i++)
	{
		data[i] = atof(argv[i + 1]);
	}
	selectionSort(0, argc - 2, data);
	for (int i = 0; i < argc - 1; i++)
	{
		cout << data[i] << " ";
	}
	return 0;
}
