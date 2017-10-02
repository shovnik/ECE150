#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
    int P;
    int Q;

    P = atoi(argv[1]);
    Q = atoi(argv[2]);

    cout << "P: " << P << endl;
    cout << "Q: " << Q << endl;
    cout << "P AND Q: " << (P && Q) << endl;
    cout << "P OR Q: " << (P || Q) << endl;
    cout << "NOT P: " << (!P) << endl;
    cout << "NOT Q: " << (!Q) << endl;

    return 0;
}
