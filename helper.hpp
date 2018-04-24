#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include <climits>
#include <cmath>
#include <utility>
#include <algorithm>

typedef unsigned int uint;
typedef std::vector<uint> v_uint;
typedef unsigned long long int ulli;
#define TABLES_PER_THREAD 1
#define RANDOM_SEED 123
#define HASH_LEN 5
#define TOLERANCE 2

class Seq 
{
		uint minLen, maxLen;
		std::vector<std::string> subseqs;
public:
		Seq() { minLen = UINT_MAX; maxLen = 0; }
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
		uint getElementLength(const int i) const 
		{ return subseqs[i].length(); }
};

uint convert(const char bp);
Seq openAndReadFile(std::string);
v_uint generateRand(uint, uint);
void threadWork(const Seq &, const Seq &, const ulli, double []);
void fillTable(std::pair<v_uint, v_uint> [], const Seq &, const Seq &);
int getMatches(pair<v_uint, v_uint> [], const ulli, const Seq &norm, const Seq &rand);