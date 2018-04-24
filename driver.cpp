#include <iostream>
#include "helper.hpp"

using namespace std;

int
main(int argc, const char* argv[])
{
		string fNames[2];
		Seq rand, norm;
		ulli maxInd = (ulli) pow(4, HASH_LEN);
		uint threadCount = thread::hardware_concurrency();

		//the threads to create
		thread threads[threadCount];
		//the results of each thread for the number of tables 
		//they are going to make
		double results[threadCount][TABLES_PER_THREAD];

		for(int i = 1; i < argc; i++)
				fNames[i-1] = string(argv[i]);

		//norm.setLens();
		norm = openAndReadFile(fNames[0]);	
		rand = openAndReadFile(fNames[1]);
		//for each thread allowed on this system
		for(uint i = 0; i < thread::hardware_concurrency(); i++)	
				threads[i] = thread(threadWork, norm, rand, maxInd, results[i]);
		for(uint i = 0; i < thread::hardware_concurrency(); i++)	
				threads[i].join();
		//TODO: Analyze the results here
		//float result = getSimilarity();
		return 0;
}

/*
		* := task completed
		*1) Create a vector of strings that are the normal sequence
		*1a) Calculate minimum string length
		*2) Create a vector of strings that are the random sequence
		*3) Generate the m random indices
		*4) Create the threads 
				--Thread view --
				*1)Randomize the hashes to look up
				*2)Sort them in ascending order
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
		5) Generate the results from each table
		6) Analyze the results
*/
