#include <cfloat>
#include <cmath>

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

bool stringToFloat(const char input[], float& value);


bool stringToFloat(const char input[], float& value) {
  value = 0;
  int i = 0;
  bool pos1 = true;
  if (input[i] == 43) {
    i++;
  }
  else if (input[i] == 45) {
    pos1 = false;
    i++;
  }
  while (input[i] > 47 && input[i] < 58) {
    if ((FLT_MAX - (input[i] - 48)) / 10 < value) {
      return false;
    }
    value *= 10;
    value += input[i] - 48;
    i++;
  }
  if (input[i] == 69 || input[i] == 101) {
    if (i == 0) {
      value = 1;
    }
    bool pos2 = true;
    i++;
    if (input[i] == 43) {
      i++;
    }
    else if (input[i] == 45) {
      pos2 = false;
      i++;
    }
    if ((input[i] < 48 && input[i] != 46) || input[i] > 57) {
      return false;
    }
    if (input[i] > 47 && input[i] < 58) {
      float e = 0;
      while (input[i] > 47 && input[i] < 58) {
        if ((FLT_MAX_EXP - (input[i] - 48)) / 10 < e) {
          return false;
        }
        e *= 10;
        e += input[i] - 48;
        i++;
      }
      if (input[i] == 46) {
        i++;
        int decimal = 1;
        if (input[i] > 47 && input[i] < 58) {
          while (input[i] > 47 && input[i] < 58) {
            e += (input[i] - 48.0) / pow(10, decimal);
            decimal++;
            i++;
          }
        }
        else {
          return false;
        }
      }
      if (pos2) {
        if (FLT_MAX / pow(10, e) < value) {
          return false;
        }
        value *= pow(10, e);
      }
      else {
        if (FLT_MIN * pow(10, e) > value) {
          return false;
        }
        value /= pow(10, e);
      }
    }
  }
  else if (input[i] == 46) {
    i++;
    int decimal = 1;
    int decimalLimit = 31;
    bool zeros = true;
    if (input[i] > 47 && input[i] < 58) {
      while (input[i] > 47 && input[i] < 58) {
        if (input[i] == 48 && zeros) {
          decimalLimit++;
        }
        else {
          zeros = false;
        }
        if (decimal > decimalLimit) {
          return false;
        }
        value += (input[i] - 48.0) / pow(10, decimal);
        decimal++;
        i++;
      }
    }
    else {
      return false;
    }
    if (input[i] == 69 || input[i] == 101) {
      bool pos2 = true;
      i++;
      if (input[i] == 43) {
        i++;
      }
      else if (input[i] == 45) {
        pos2 = false;
        i++;
      }
      if ((input[i] < 48 && input[i] != 46) || input[i] > 57) {
        return false;
      }
      if (input[i] > 47 && input[i] < 58) {
        float e = 0;
        while (input[i] > 47 && input[i] < 58) {
          if ((FLT_MAX_EXP - (input[i] - 48)) / 10 < e) {
            return false;
          }
          e *= 10;
          e += input[i] - 48;
          i++;
        }
        if (input[i] == 46) {
          i++;
          int decimal = 1;
          if (input[i] > 47 && input[i] < 58) {
            while (input[i] > 47 && input[i] < 58) {
              e += (input[i] - 48.0) / pow(10, decimal);
              decimal++;
              i++;
            }
          }
          else {
            return false;
          }
        }
        if (pos2) {
          if (FLT_MAX / pow(10, e) < value) {
            return false;
          }
          value *= pow(10, e);
        }
        else {
          if (FLT_MIN * pow(10, e) > value) {
            return false;
          }
          value /= pow(10, e);
        }
      }
      else {
        return false;
      }
    }
  }
  if (!pos1) {
    value *= - 1;
  }
  if (input[i] == '\0') {
    return true;
  }
  return false;
}


#ifndef MARMOSET_TESTING
int main(const int argc, const char* const argv[]) {

  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1))
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
  return 0;
}

#endif
