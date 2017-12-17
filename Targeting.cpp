#include <stdlib.h>
#include <math.h>
#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN()
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b,
							 const float w, float& theta);

bool hitTargetGivenAngle (const float h, const float m, const float theta,
							const float d, const float t, const float b,
							const float w, float& v);


bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b,
							 const float w, float& theta) {
	if (h < 0 || v < 0 || m <= 0 || d < 0 || b < 0 || w < 0) {
		return false;
	}
	float a = - (9.81 * pow(d, 2)) / (2 * pow(v, 2));
	float c = h - t - (9.81 * pow(d, 2)) / (2 * pow(v, 2));
	if (pow(d, 2) - 4 * a * c < 0) {
		return false;
	}
	theta = (atan((-d - sqrt(pow(d, 2) - 4 * a * c)) / (2 * a))) * (180 / (2 * acos(0)));
	return true;
}

bool hitTargetGivenAngle (const float h, const float m, const float theta,
							const float d, const float t, const float b,
							const float w, float& v) {
	if (h < 0 || m <= 0 || d < 0 || b < 0 || w < 0) {
			return false;
	}
	float temp = (9.8 * pow(d, 2)) / (2 * pow(cos(theta * (2 * acos(0)) / 180), 2) * (h - t + d * tan(theta * (2 * acos(0)) / 180)));
	if (temp < 0) {
		return false;
	}
	v = sqrt(temp);
	return true;
}


#ifndef MARMOSET_TESTING
int main() {

  // Some test driver code here ....

  float h = 50;
  float d = 60;
  float b = 40;
  float t = 30;
  float w = 30;
  float m = 1;

  float theta = 45; // Angle in degrees;
  float v = 25;

  cout << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity\n\n";
  }

  cout << "Given initial velocity: " << v << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenVelocity (h, v, m, d, t, b, w, theta)) {
    cout << "required angle: " << theta << endl << endl;
  }
  else {
    cout << "cannot calculate the angle\n\n";
  }

  return 0;
}
#endif
