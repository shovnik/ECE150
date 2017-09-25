#include <iostream>
#include <stdlib.h>
#include <limits.h> 
#include <float.h>
#include <math.h>

using namespace std;

int main(const int argc, const char*const argv[]) {

int N = atoi(argv[1]);
int S = atoi(argv[2]);

int leftShift = N*pow(2, S);
int rightShift = N/pow(2, S);

cout << "N: " << N << endl;
cout << "S: " << S << endl;
cout << "Left-shift of N by S bits is: " << (N<<S) << endl;
cout << "Right-shift of N by S bits is: " << (N>>S) << endl;
cout << "The equivalent math operation of left-shift N by S bits is: N multiplied by 2 to the power of S" << endl;
cout << "And the result of that operation is: " << leftShift << endl;
cout << "The equivalent math operation of right-shift N by S bits is: N divided by 2 to the power of S rounded towards negative infinity" << endl;
cout << "And the result of that operation is: " << rightShift << endl;

return 0; }