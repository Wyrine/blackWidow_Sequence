#include <iostream>
#include "helper.hpp"

using namespace std;

int
main(int argc, const char* argv[])
{
		string fNames[2];
		uint threadCount = thread::hardware_concurrency();
		int minLen, minLen2;
		minLen = minLen2 = INT_MAX;
		vector<string> rand, norm;

		for(int i = 1; i < argc; i++)
				fNames[i-1] = string(argv[i]);

		norm = openAndReadFile(fNames[0], minLen);	
		rand = openAndReadFile(fNames[1], minLen2);
		minLen = (minLen > minLen2) ? minLen : minLen2;
		return 0;
}

/*
1) Read each 'query' string from the main strand into memory
		1) Create a vector of strings that are the normal sequence
		1a) Calculate minimum string length
		2) Create a vector of strings that are the random sequence
		3) Create the threads 
				--Thread view --
				1)Randomize the hashes to look up
				2)Sort them in ascending order
				for(int i = 0; i < s1.length(); i++){
						for(int j = 0; j < hashes.length(); j++)
						{
								int c = convert(s1[i][hashes[j]]);
								//can probably do s2 here too
								~~~~~~~check this next line, unsure about these offsets~~~~~~~
								c = c << (hashes.length() - count)*2; //count starts at 1
								//insert into hash table
						}
				}
*/
