#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include <climits>
#include <random>

typedef unsigned int uint;
#define TABLES_PER_THREAD 1
#define RANDOM_SEED 123

class Seq 
{
		uint minLen, maxLen;
		std::vector<std::string> subseqs;
public:

		Seq() { minLen = UINT_MAX; maxLen = 0; }
		//void setMin(uint x) { minLen = x; }
		//void setMax(uint x) { maxLen = x; }
		void addSeq(std::string s) 
		{ //add s and update min and max, if applicable 
				subseqs.push_back(s); 
				if(s.length() < minLen) minLen = s.length();
				if(s.length() > maxLen) maxLen = s.length();
		}
		uint getMin() const { return minLen; }
		uint getMax() const { return maxLen; }
		uint getSize() const { return subseqs.size(); }
		std::string getElement(const int i) const { return subseqs[i]; }	
};

uint convert(const char bp);
Seq openAndReadFile(std::string);
std::vector<uint> generateRand(uint, uint);
