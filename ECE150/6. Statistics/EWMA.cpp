#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char*const argv[]) {                            

	if ((argc -3) <= 0) {
		cerr << "Unable to compute statistics over data set because data set is empty." << endl;
	}

	else if (atof(argv[2]) < 0) {
		cerr << "Unable to compute statistics over data set because age limit is negative." << endl;
	}

	else if (((atof(argv[1])) < 0) || ((atof(argv[1])) > 1)) {
		cerr << "Unable to compute statistics over data set because alpha is not within allowed range." << endl;
	}

	else {
		int i = 1;                                  //sample number
		int j = 3;                                  //sample location in argv array
		int k;                                      //sample location in argv array within nested loops
		float min = atof(argv[j]);                  //minimum floating-point number
		float max = atof(argv[j]);                  //maximum floating-point number
		float EWMA = atof(argv[j]);                 //EWMA of floating-point numbers
		int minS = 1;                               //sample number of current minimum
		int maxS = 1;                               //sample number of current maximum

		const char s = ' ';                         //separator
		const int w = 10;                           //width per slot

		cout << left << setw(w) << setfill(s) << "Sample";
		cout << left << setw(w) << setfill(s) << "Value";
		cout << left << setw(w) << setfill(s) << "Minimum";
		cout << left << setw(w) << setfill(s) << "EWMA";
		cout << left << setw(w) << setfill(s) << "Maximum";
		cout << endl;

		while (i <= (argc - 3)) {
			j = i + 2;                              
			EWMA = atof(argv[1])*atof(argv[j]) + (1 - atof(argv[1]))*EWMA;
					
			if (atof(argv[j]) <= min) {
				min = atof(argv[j]);
				minS = i;
			}

			if (i - minS == atoi(argv[2])) {
				k = j - atoi(argv[2]) + 1;
				min = atof(argv[k]);

				while (k <= j) {
					if (atof(argv[k]) <= min) {
						min = atof(argv[k]);
						minS = (k - 2);
					}

					k += 1;
				}
			}
	
			if (atof(argv[j]) >= max) {
				max = atof(argv[j]);
				maxS = i;
			}

			if (i - maxS == atoi(argv[2])) {
				k = j - atoi(argv[2]) + 1;
				max = atof(argv[k]);

				while (k <= j) {
					if (atof(argv[k]) >= max) {
						max = atof(argv[k]);
						maxS = (k - 2);
					}

					k += 1;
				}
			}

			cout << left << setw(w) << setfill(s) << i;
			cout << left << setw(w) << setfill(s) << atof(argv[j]);
			cout << left << setw(w) << setfill(s) << min;
			cout << left << setw(w) << setfill(s) << EWMA;
			cout << left << setw(w) << setfill(s) << max;
			cout << endl;

			i += 1;
		}
	}
}
