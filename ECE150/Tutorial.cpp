#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char* const argv[]) 
{
	int first_num = atoi(argv[1]);
	int second_num = atoi(argv[2]);

	int sum = first_num + second_num;
	int product = first_num * second_num;

	cout << "sum: " << sum << endl;
	cout << "product: " << product << endl;

	return 0; 
}