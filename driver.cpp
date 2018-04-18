#include <iostream>
#include "helper.hpp"

using namespace std;

int
main(int argc, const char* argv[])
{
		string fNames[2];
		uint threadCount = thread::hardware_concurrency();
		
		for(int i = 1; i < argc; i++)
				fNames[i-1] = string(argv[i]);
		cout << threadCount << endl;

		return 0;
}

/*
1) Read each 'query' string from the main strand into memory
		1) Create a vector of strings that are the normal sequence
		2) Create a vector of strings that are the random sequence
		3) Create the threads 
				--Thread view --
				1)Randomize the indices to look up
				2)Sort them in ascending order
				for(int i = 0; i < s1.length(); i++){
						for(int j = 0; j < indices.length(); j++)
						{
								int c = convert(s1[i][indices[j]]);
								//can probably do s2 here too
								~~~~~~~check this next line, unsure about these offsets~~~~~~~
								c = c << indices[indices.length() - j - 1] - 1;
								//insert into hash table
						}
				}



*/
