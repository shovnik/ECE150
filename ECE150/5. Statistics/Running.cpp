#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char*const argv[]) {
	if (argc < 2) {
		cerr << "Unable to compute statistics over data set because data set is empty." << endl;
	}

	float sum = 0;							        //sum of floating-point numbers
	float avg = 0;								    //average of floating-point numbers
	float min = atof(argv[1]);						//minimum floating-point number
	float max = atof(argv[1]);						//maximum floating-point number
	
	const char s = ' ';								//separator
	const int w = 10;								//width per slot

	cout << left << setw(w) << setfill(s) << "Sample";
	cout << left << setw(w) << setfill(s) << "Value";
	cout << left << setw(w) << setfill(s) << "Minimum";
	cout << left << setw(w) << setfill(s) << "Average";
	cout << left << setw(w) << setfill(s) << "Maximum";
	cout << endl; 
	

	int i = 1;									   	//index for while loop
	while (i <= argc - 1) {
		sum += atof(argv[i]);
		avg = sum / i;

		if (atof(argv[i]) < min) {
			min = atof(argv[i]);
		}

		if (atof(argv[i]) > max) {
			max = atof(argv[i]);
		}
		
		cout << left << setw(w) << setfill(s) << i;
		cout << left << setw(w) << setfill(s) << atof(argv[i]);
		cout << left << setw(w) << setfill(s) << min;
		cout << left << setw(w) << setfill(s) << avg;
		cout << left << setw(w) << setfill(s) << max;
		cout << endl;
		
		i += 1;
	}
	
return 0; 
}
