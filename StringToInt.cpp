#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif


bool stringToInt(const char input[], int& value);

bool stringToInt(const char input[], int& value) {
  int i = 0;
  value = 0;
  bool positive = true;
  if (input[0] == 43) {
    i++;
  }
  else if (input[0] == 45) {
    positive = false;
    i++;
  }
  while (input[i] != '\0') {
    if (input[i] > 47 && input[i] < 58) {
      if ((2147483647 - (input[i] - 48)) / 10 < value) {
        return false;
      }
      value *= 10;
      value += input[i] - 48;
    }
    else {
      return false;
    }
    i++;
  }
  if (!positive) {
    value *= -1;
  }
  return true;
}

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  //NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  int argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
    return -1;
  }

  if (stringToInt(argv[1],argv1))
    cout << "argv[1] is an int with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not an int." << endl;
  return 0;
}

#endif
