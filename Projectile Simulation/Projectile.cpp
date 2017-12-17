#include <stdlib.h>
#include <math.h>


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif


bool projectileDestination(const float h, const float v, const float m, const float theta,
    const float d, const float t, const float b, const float w, float& destX, float& destY);


bool projectileDestination(const float h, const float v, const float m, const float theta,
    const float d, const float t, const float b, const float w, float& destX, float& destY)
{
    if (h < 0 || t < 0 || v < 0 || m <= 0 || theta < 0 || theta > 180 || w == 0 || b == 0
        || (b > 0 && b + w < 0) || (b < 0 && b + w > 0))
    {
        return false;
    }
    if (v == 0 || theta == 90)
    {
        destX = 0;
        destY = h;
        return true;
    }

    const float PI = 2 * acos(0);
    float deltaY = (t - h);
    float deltaT
        = (-v * sin(theta * PI / 180) - sqrt(pow(v * sin(theta * PI / 180), 2) - 2 * 9.8 * deltaY))
        / (-9.8);
    float deltaX = v * cos(theta * PI / 180) * deltaT;
    if (b > 0)
    {
        if (deltaX >= b && deltaX <= b + w)
        {
            destX = deltaX;
            destY = t;
            return true;
        }
        else if (deltaX > 0 && deltaX < b)
        {
            deltaY = -h;
            deltaT = (-v * sin(theta * PI / 180)
                         - sqrt(pow(v * sin(theta * PI / 180), 2) - 2 * 9.8 * deltaY))
                / (-9.8);
            deltaX = v * cos(theta * PI / 180) * deltaT;
            if (deltaX <= b)
            {
                destX = deltaX;
                destY = 0;
                return true;
            }
            else
            {
                destX = b;
                deltaT = b / (v * cos(theta * PI / 180));
                destY = h + deltaT * v * sin(theta * PI / 180) - pow(deltaT, 2) * 4.9;
                return true;
            }
        }

        else
        {
            if (theta < 90)
            {
                deltaX = b;
                deltaT = b / (v * cos(theta * PI / 180));
                deltaY = h + deltaT * v * sin(theta * PI / 180) - pow(deltaT, 2) * 4.9;
                if (deltaY >= 0 && deltaY <= t)
                {
                    destX = b;
                    destY = deltaY;
                    return true;
                }
            }
            deltaY = -h;
            deltaT = (-v * sin(theta * PI / 180)
                         - sqrt(pow(v * sin(theta * PI / 180), 2) - 2 * 9.8 * deltaY))
                / (-9.8);
            destX = v * cos(theta * PI / 180) * deltaT;
            destY = 0;
            return true;
        }
    }
    else
    {
        if (deltaX <= b && deltaX >= b + w)
        {
            destX = deltaX;
            destY = t;
            return true;
        }
        else if (deltaX < 0 && deltaX > b)
        {
            deltaY = -h;
            deltaT = (-v * sin(theta * PI / 180)
                         - sqrt(pow(v * sin(theta * PI / 180), 2) - 2 * 9.8 * deltaY))
                / (-9.8);
            deltaX = v * cos(theta * PI / 180) * deltaT;
            if (deltaX >= b)
            {
                destX = deltaX;
                destY = 0;
                return true;
            }
            else
            {
                destX = b;
                deltaT = b / (v * cos(theta * PI / 180));
                destY = h + deltaT * v * sin(theta * PI / 180) - pow(deltaT, 2) * 9.8 / 2;
                return true;
            }
        }

        else
        {
            if (theta > 90)
            {
                deltaX = b;
                deltaT = b / (v * cos(theta * PI / 180));
                deltaY = h + deltaT * v * sin(theta * PI / 180) - pow(deltaT, 2) * 9.8 / 2;
                if (deltaY >= 0 && deltaY <= t)
                {
                    destX = b;
                    destY = deltaY;
                    return true;
                }
            }
            deltaY = -h;
            deltaT = (-v * sin(theta * PI / 180)
                         - sqrt(pow(v * sin(theta * PI / 180), 2) - 2 * 9.8 * deltaY))
                / (-9.8);
            destX = v * cos(theta * PI / 180) * deltaT;
            destY = 0;
            return true;
        }
    }
}


#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[])
{

    // Some test driver code here ....

    float h = 10;
    float v = 10;
    float m = 10;
    float theta = 135; // Angle in degrees; will need to be converted by function
    float d = 100;
    float t = 5;
    float b = -14;
    float w = -5;

    float hitsAtX;
    float hitsAtY;

    if (projectileDestination(h, v, m, theta, d, t, b, w, hitsAtX, hitsAtY))
        cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" << endl;
    else
        cout << "Unable to calculate where projectile hits." << endl;
    return 0;
}

#endif
