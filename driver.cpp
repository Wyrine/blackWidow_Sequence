#include <iostream>
#include "helper.hpp"

using namespace std;

int
main(int argc, const char* argv[])
{
		string names[2];
		uint threadCount = thread::hardware_concurrency();
		
		for(int i = 1; i < argc; i++)
				names[i-1] = string(argv[i]);
		cout << threadCount << endl;

		return 0;
}
