#include <fstream>
using namespace std;

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

int maxNumErrors = 10;

int histogram(const char filename[], int histogram[10],
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);

bool stringToInt(const char input[], int& value, int& i) {
  value = 0;
  bool positive = true;
  if (input[i] == 43) {
    i++;
  }
  else if (input[i] == 45) {
    positive = false;
    i++;
  }
  while (input[i] > 47 && input[i] < 58) {
    if ((2147483647 - (input[i] - 48)) / 10 < value) {
      return false;
    }
    value *= 10;
    value += input[i] - 48;
    i++;
  }
  if (!positive) {
    value *= -1;
  }
  return true;
}


bool skipSpaces(const char line[], int& i, int maxLineLength) {
  while (i < maxLineLength && (line[i] < 48 || line[i] > 57) && line[i] != 43 && line[i] != 45) {
    if (line[i] < 33) {
      i++;
    }
    else {
      return false;
    }
  }
  if (i == maxLineLength) {
    return false;
  }
  return true;
}


bool parseLine (char line[], int& studentID, int& grade, int maxLineLength) {
  int i = 0;
  if (skipSpaces(line, i, maxLineLength)) {
    if (stringToInt(line, studentID, i)) {
      while (i < maxLineLength && line[i] != 44) {
        if (line[i] < 33) {
          i++;
        }
        else {
          return false;
        }
      }
      i++;
      if (skipSpaces(line, i, maxLineLength)) {
        if (stringToInt(line, grade, i)) {
          return true;
        }
      }
    }
  }
  return false;
}


void insertIntoHistogram(int& studentID, int& grade, int histogram[], int minAcceptableID, int maxAcceptableID, int fileLineNumber, int rejected[], int& numberOfRejects) {
  if (studentID >= minAcceptableID && studentID <= maxAcceptableID && grade >= 0 && grade <= 100) {
    int bracket = grade / 10;
    if (bracket >= 0 && bracket < 10) {
      histogram[bracket]++;
    }
    else {
      histogram[9]++;
    }
  }
  else {
    if (numberOfRejects < maxNumErrors) {
      rejected[numberOfRejects] = fileLineNumber;
    }
    numberOfRejects++;
  }
  return;
}


int histogram(const char filename[], int histogram[10],
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects) {
  const int maxLineLength = 100;
  char line[maxLineLength];
  ifstream infile; //declare file object
  infile.open(filename);
  if (minAcceptableID > maxAcceptableID || histogram == NULL || !infile.is_open()) {
    return -1;
  }
  bool done = false;
  int fileLineNumber = 0;
  for (int i = 0; i < 10; i++) {
    histogram[i] = 0;
  }
  int numberOfRejects = 0;
  int rejected[maxNumErrors];
  while (!done) {
    ++fileLineNumber;
    if (!infile.getline(line, maxLineLength)) {
      if (infile.eof()) {
        done = true;
      }
      else {
        return -1;
      }
    }
    else {
      int studentID = 0;
      int grade = 0;
      if (parseLine(line, studentID, grade, maxLineLength)) {
        insertIntoHistogram(studentID, grade, histogram, minAcceptableID, maxAcceptableID, fileLineNumber, rejected, numberOfRejects);
        if (numberOfRejects > 9) {
          return -1;
        }
      }
      else {
        return -1;
      }
    }
  }
  if (numberOfRejects > 0) {
    rejects = new int[numberOfRejects];
    for (int i = 0; i < numberOfRejects; i++) {
      rejects[i] = rejected[i];
    }
  }
  bool data = false;
  int k = 0;
  while (!data && k < 10) {
    if (histogram[k] > 0) {
      data = true;
    }
    k++;
  }
  if (!data) {
    return -1;
  }
  return numberOfRejects;
}


#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {

  // Some test driver code here ....
  if (argc < 2) {

  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int  buckets[numBuckets];
  int* rejectedRecords = NULL;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
      cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i){
      if (i != numBuckets-1) {
        cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
      }
      else {
        cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
      }
    }
    if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i)
	      cout << " " << rejectedRecords[i];
      cout << endl;
      delete[] rejectedRecords;
    }
  }
  return 0;
}

#endif
