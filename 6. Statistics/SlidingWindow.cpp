#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char* const argv[])
{

    if ((argc - 2) < 1)
    {
        cerr << "Error: Insufficient arguments; expecting at least 2 arguments." << endl;
    }

    else if (atoi(argv[1]) < 1)
    {
        cerr << "Error: Unable to compute statistics over data set because window size needs to be "
                "at least 1."
             << endl;
    }

    else
    {
        int SWsize = atoi(argv[1]); // sliding window size
        if (SWsize == 1)
        {
            cerr << "Warning: Since window size is equal to 1, all statistics are simply equal to "
                    "the sample value and provide no insight."
                 << endl;
        }
        if (SWsize > (argc - 2))
        {
            cerr << "Warning: No advantage is gained from using a sliding window statistical "
                    "analysis over a running one since the window size is currently greater than "
                    "the data set."
                 << endl;
        }

        int i;
        int j;
        float arr[1000];
        for (i = 0; i < (SWsize - 1); i++)
        {
            arr[i] = atof(argv[2]);
        }
        for (i = (SWsize - 1); i < (SWsize + argc - 3); i++)
        {
            arr[i] = atof(argv[(i - SWsize + 3)]);
        }

        float SWmin = arr[0]; // sliding window maximum of data set
        float SWmax = arr[0]; // sliding window maximum of data set
        float SWsum; // sliding window sum of data set
        float SWavg; // sliding window average of data set
        int minI = 0; // array index of current minimum
        int maxI = 0; // array index of current maximum

        const char s = ' '; // separator
        const int w = 10; // width per slot

        cout << "Window Size: " << SWsize << endl;
        cout << left << setw(w) << setfill(s) << "Sample";
        cout << left << setw(w) << setfill(s) << "Value";
        cout << left << setw(w) << setfill(s) << "SWMinimum";
        cout << left << setw(w) << setfill(s) << "SWAverage";
        cout << left << setw(w) << setfill(s) << "SWMaximum";
        cout << endl;

        for (i = 0; i < (SWsize + argc - 3); i++)
        {
            if (arr[i] <= SWmin)
            {
                SWmin = arr[i];
                minI = i;
            }

            if (i - minI == SWsize)
            {
                SWmin = arr[i - SWsize + 1];
                minI = i - SWsize + 1;

                for (j = (i - SWsize + 2); j <= i; j++)
                {
                    if (arr[j] <= SWmin)
                    {
                        SWmin = arr[j];
                        minI = j;
                    }
                }
            }

            if (arr[i] >= SWmax)
            {
                SWmax = arr[i];
                maxI = i;
            }

            if (i - maxI == SWsize)
            {
                SWmax = arr[i - SWsize + 1];
                maxI = i - SWsize + 1;

                for (j = (i - SWsize + 2); j <= i; j++)
                {
                    if (arr[j] >= SWmax)
                    {
                        SWmax = arr[j];
                        maxI = j;
                    }
                }
            }

            if (i > (SWsize - 2))
            {
                SWsum = 0;
                for (j = (i - SWsize + 1); j <= i; j++)
                {
                    SWsum += arr[j];
                }
                SWavg = SWsum / SWsize;

                cout << left << setw(w) << setfill(s) << (i - SWsize + 2);
                cout << left << setw(w) << setfill(s) << arr[i];
                cout << left << setw(w) << setfill(s) << SWmin;
                cout << left << setw(w) << setfill(s) << SWavg;
                cout << left << setw(w) << setfill(s) << SWmax;
                cout << endl;
            }
        }
    }
}
