#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char*const argv[]) {
	int num = argc - 1;                                //number of floating-point numbers

	if (num == 0) {
		cerr << "Error: Unable to compute statistics over data set because data set is empty." << endl;
	}

	if (num > 0) {
		float sum = 0;                              //sum of floating-point numbers
		float min = atof(argv[1]);                  //minimum floating-point number
		float max = atof(argv[1]);                  //maximum floating-point number

		int i = 1;                                  //index for while loop
		while (i <= num) {
			sum += atof(argv[i]);

			if (atof(argv[i]) < min) {
				min = atof(argv[i]);
			}

			if (atof(argv[i]) > max) {
				max = atof(argv[i]);
			}

			i += 1;
		}

		float avg = sum / num;                      //average of floating-point numbers 

		cout << "Number of floating-point numbers: " << num << endl;
		cout << "Minimum floating-point number: " << min << endl;
		cout << "Average floating-point number: " << avg << endl;
		cout << "Maximum floating-point number: " << max << endl;
	}
}
