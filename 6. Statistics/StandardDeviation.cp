#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
    if (argc < 2)
        cerr << "Error: Unable to compute statistics over data set because data set is empty."
             << endl;

    else
    {
        int i;
        float arr[50];
        for (i = 0; i < (argc - 1); i++)
        {
            arr[i] = atof(argv[i + 1]);
        }

        float sum = 0; // sum of floating-point numbers
        float min = atof(argv[1]); // minimum floating-point number
        float max = atof(argv[1]); // maximum floating-point number
        for (i = 0; i < argc - 1; i++)
        {
            sum += arr[i];

            if (arr[i] < min)
                min = arr[i];

            if (arr[i] > max)
                max = arr[i];
        }

        float avg = sum / (argc - 1); // average of floating-point numbers
        float sumdif = 0;
        for (i = 0; i < argc - 1; i++)
        {
            sumdif += pow((arr[i] - avg), 2);
        }
        float pstd = sqrt(sumdif / (argc - 1));
        float sstd = sqrt(sumdif / (argc - 2));

        cout << "Number of floating-point numbers: " << argc - 1 << endl;
        cout << "Minimum floating-point number: " << min << endl;
        cout << "Average floating-point number: " << avg << endl;
        cout << "Maximum floating-point number: " << max << endl;
        cout << "Population standard deviation: " << pstd << endl;
        if (argc == 2)
            cout << "Sample standard deviation: infinity" << endl;
        else
            cout << "Sample standard deviation: " << sstd << endl;
    }
}
