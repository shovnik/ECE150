#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;

int main(const int argc, const char*const argv[]) {
	if (argc < 4) {
		cerr << "Error: Insufficient arguments; expecting 3 arguments." << endl;
	}

	else {
		if (argc > 4) {
			cerr << "Warning: Expecting three command-line arguments; received " << (argc - 1) << "; ignoring extraneous arguments." << endl;
		}

		float v = atof(argv[1]);                                                //velocity
		float d = atof(argv[2]);                                                //distance
		float maxDec = atof(argv[3]);                                           //maximum deceleration allowed
		
		if (v == 0) {
			cout << "There is no possibility of collision because the car is stationary." << endl;
		}

		else if (((v < 0) && (d > 0)) || ((v > 0) && (d < 0))) {
			cout << "There is no possibility of collision because the car is moving away from the obstacle." << endl;
		}

		else {
			float minDec = pow(v, 2) / (2 * abs(d));                            //minimum deceleration to stop in time
			if (minDec <= maxDec) {
				float maxT = abs(v) / abs(minDec);                              //maximum stopping time with minimum deceleration
				cout << "Initial velocity: " << v << " m/s" << endl;
				cout << "Distance to obstacle: " << d << " m" << endl;
				cout << "Minimum deceleration: " << minDec << " m/s/s" << endl;
				cout << "Maximum stopping time: " << maxT << " s" << endl;
				}

			else {
				float crashV = sqrt(pow(v, 2) - 2 * abs(d) * abs(maxDec));       //positive velocity at crash with maximum deceleration
				float crashT = (abs(v) - abs(crashV)) / abs(maxDec);             //time before imminent crash with positive velocity
				cout << "Crash will occur in " << crashT << " seconds at velocity " << crashV << "m/s; deploying airbags." << endl;
			}
		}
	}
}