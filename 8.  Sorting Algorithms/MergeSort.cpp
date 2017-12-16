#include <iostream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;


int merge(float arr[], int start1, int split, int end2)
{
    int offset = start1;
    int size = end2 - offset + 1;
    float tmpArray[size];
    for (int i = 0; i < size; i++)
    {
        tmpArray[i] = arr[i + start1];
    }
    int smallestElement1 = 0;
    int smallestElement2 = split + 1 - offset;
    int nextSortedElement = start1;
    while (nextSortedElement <= end2)
    {
        if ((smallestElement1 <= split - offset) && (smallestElement2 <= end2 - offset))
        {
            if (tmpArray[smallestElement1] < tmpArray[smallestElement2])
            {
                arr[nextSortedElement] = tmpArray[smallestElement1];
                smallestElement1++;
            }
            else
            {
                arr[nextSortedElement] = tmpArray[smallestElement2];
                smallestElement2++;
            }
        }
        else if (smallestElement1 <= split - offset)
        {
            arr[nextSortedElement] = tmpArray[smallestElement1];
            smallestElement1++;
        }
        else
        {
            arr[nextSortedElement] = tmpArray[smallestElement2];
            smallestElement2++;
        }
        nextSortedElement++;
    }
}


void mergeSort(float arr[], int start, int end)
{
    if (start < end)
    {
        int split = (start + end) / 2;
        mergeSort(arr, start, split);
        mergeSort(arr, split + 1, end);

        merge(arr, start, split, end);
    }
}


int main(const int argc, const char* argv[])
{
    float data[argc - 1];
    for (int i = 0; i < argc - 1; i++)
    {
        data[i] = atof(argv[i + 1]);
    }
    mergeSort(data, 0, argc - 2);
    for (int i = 0; i < argc - 1; i++)
    {
        cout << data[i] << " ";
    }
    return 0;
}
