#include <stdlib.h>
#include <math.h>
#include <limits>

using namespace std;

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN()
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

bool hitTargetGivenAngle (const float h, const float m, const float theta,
              const float d, const float step, const float k,
              const float t, const float b, const float w, float& v);


  double chooChoo(const double x, const double y, const double km, const double angle,
     const double step, const double t, const double vx, const double vy) {
     double newX = x;
     double newY = y;
     double newVx = vx;
     double newVy = vy;
     double newV = sqrt(pow(newVx, 2) + pow(newVy, 2));
     double newAngle = angle;
     bool enough = false;
     while (newY >= t || !enough) {
       newX = newX + step * newVx;
       newY = newY + step * newVy;
       newV = sqrt(pow(newVx, 2) + pow(newVy, 2));
       newAngle = atan(newVy / newVx);
       newVx = newVx - step * km * newV * newVx;
       newVy = newVy - step * (9.8 + km * newV * newVy);
       if (newY >= t) {
         enough = true;
       }
       if (newY < 0 && !enough) {
         enough = true;
         return - 10;
       }
     }
     return newX;
  }


double f(const double v, const double h, const double m, const double theta,
  const double d, const double step, const double k, const double t) {
    const double angle = theta * acos(0) / 90;
    const double vx = v * cos(angle);
    const double vy = v * sin(angle);
    const double km = k / m;
    const double distance = chooChoo(0, h, km, angle, step, t, vx, vy);
    const double distanceFromD = distance - d;
  return distanceFromD;
}


int iteration;


double bisectionHelper(const double left, const double right, const double h, const double m, const double theta,
    const double d, const double step, const double k, const double t, const int maxIterations) {
  iteration++;
  const double midpoint = (left + right) / 2;
  const double funcLeft = f(left, h, m, theta, d, step, k, t);
  const double funcRight = f(right, h, m, theta, d, step, k, t);
  const double funcMidpoint = f(midpoint, h, m, theta, d, step, k, t);
  if (iteration > maxIterations) {
    return midpoint;
  }
  if (funcMidpoint == 0) {
    return midpoint;
  }
  else if (funcLeft * funcMidpoint > 0) {
    return bisectionHelper(midpoint, right, h, m, theta, d, step, k, t, maxIterations);
  }
  else if (funcRight * funcMidpoint > 0) {
    return bisectionHelper(left, midpoint, h, m, theta, d, step, k, t, maxIterations);
  }
}

double bisection(const double left, const double right, const double h, const double m, const double theta,
		const double d, const double step, const double k, const double t) {
  iteration = 0;
  const double funcLeft = f(left, h, m, theta, d, step, k, t);
  const double funcRight = f(right, h, m, theta, d, step, k, t);

  if (funcLeft == 0) {
    return left;
  }
  if (funcRight == 0) {
    return right;
  }
  return bisectionHelper(left, right, h, m, theta, d, step, k, t, 100);
}


bool hitCorner(const double x, const double y, const double km, const double angle,
   const double step, const double t, const double vx, const double vy, const double b,
    const float w) {
     if (w == 0) {
       return false;
     }
     double newX = x;
     double newY = y;
     double newVx = vx;
     double newVy = vy;
     double newV = sqrt(pow(newVx, 2) + pow(newVy, 2));
     double newAngle = angle;
     while (newX < b - 0.01) {
       newX = newX + step * newVx;
       newY = newY + step * newVy;
       newV = sqrt(pow(newVx, 2) + pow(newVy, 2));
       newAngle = atan(newVy / newVx);
       newVx = newVx - step * km * newV * newVx;
       newVy = newVy - step * (9.8 + km * newV * newVy);
     }
     if (newY < t) {
       return true;
     }
  return false;
}


bool hitTargetGivenAngle (const float h, const float m, const float theta,
							const float d, const float step, const float k,
              const float t, const float b, const float w, float& v) {
  if (h >= 0 && m > 0 && d >= 0 && w >= 0 && step > 0 && k >= 0 && (d >= b && d <= b + w)) {
      const double angle = theta * acos(0) / 90;
      const double km = k / m;
      double left = 0;
      double vx = left * cos(angle);
      double vy = left * sin(angle);
      while (chooChoo(0, h, km, angle, step, t, vx, vy) < 0 && left < 10000) {
        left++;
        vx = left * cos(angle);
        vy = left * sin(angle);
      }
      double right = left + 1;
      vx = right * cos(angle);
      vy = right * sin(angle);
      while (chooChoo(0, h, km, angle, step, t, vx, vy) < d && right < 10000) {
        right++;
        vx = right * cos(angle);
        vy = right * sin(angle);
      }
      left = right - 1;
      v = (float)bisection(left, right, h, m, theta, d, step, k, t);
      if (v != v) {
        return false;
      }
      vx = v * cos(angle);
      vy = v * sin(angle);
      if (hitCorner(0, h, km, angle, step, t, vx, vy, b, w)) {
        return false;
      }
      return true;
    }
  return false;
}


#ifndef MARMOSET_TESTING
int main() {

  float h = 50;
  float d = 60;
  float b = 2;
  float t = 60;
  float w = 0.1;
  float m = 0.5;
  float step = 0.001;
  float k = 0;
  float theta = 68.81; // Angle in degrees;
  float v = 25;

  cout << endl << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity" << endl << endl;
  }

  return 0;
}
#endif
