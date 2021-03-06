#include "helper.hpp"

using namespace std;

Seq
openAndReadFile(string fname)
{
		Seq rv;
		string line;
		int count = 1;
		ifstream f(fname);

		if(!f.is_open())
		{
				cerr << "Invalid file:" << fname << endl;
				exit(1);
		}
		while(getline(f, line))
		{
				if((count + 2) % 4 == 0) rv.addSeq(line);
				count++;
		}
		f.close();
		return rv;
}

uint 
getUnionCount(const Seq & norm, const Seq & rand)
{
		set<string> rv;
		uint minLen = min(norm.getMin(), rand.getMin());
		uint nCount = norm.getSize(), rCount = rand.getSize();

		for(uint i = 0; i < max(nCount, rCount); i++)
		{
				if(nCount > i)
						rv.insert(norm.getElement(i).substr(0, minLen));
				if(rCount > i)
						rv.insert(norm.getElement(i).substr(0, minLen));
		}
		return rv.size();
}

uint
convert(const char bp)
{
		uint rv = 0; // A
		switch(bp)
		{
				case 'C':
						rv = 1;
						break;
				case 'T':
						rv = 2;
						break;
				case 'G':
						rv = 3;
						break;
				default:
						break;
		}
		return rv;
}

//size is the hash size we want
//n is the string length or the maxIndex + 1
v_uint
generateRand(uint size, uint n, const ulli seed)
{
		v_uint rv;
		bool checkInit[n];

		memset(checkInit, 0, n*sizeof(bool));
		srand(seed);

		for(uint i = 0; i < size; ++i)
		{
				uint tmp = rand() % n;

				while(checkInit[tmp]) tmp = rand() % n;
				checkInit[tmp] = true;
				rv.push_back(tmp);
		}
		sort(rv.begin(), rv.begin()+size);
		return rv;
}

void
threadWork(const Seq & norm, const Seq & rand, const ulli maxInd, 
						const ulli setUnion, double myRes[])
{
		for(uint i = 0; i < TABLES_PER_THREAD; i++)
		{
				//table[i].first := vector of indices into norm
				//table[i].second := vector of indices into rand
				pair<v_uint, v_uint> table[maxInd];
				fillTable(table, norm, rand, (ulli) myRes * TABLES_PER_THREAD + i * (ulli) table);
				//TODO: The following
				/* table should now be filled with the hashes, now generate results */
				/* results should be stored in myRes to reflect back in main thread */
				//myRes[i] is the result to update
				myRes[i] = ((double) getMatches(table, maxInd, norm, rand, 1)) / setUnion; 
		}
}

uint
getMatches(pair<v_uint, v_uint> table[], const ulli maxInd, const Seq &norm, 
						const Seq &rand, const bool jacc) 
{
	int matches = 0;
	int minLen, count;
	v_uint rTemp, nTemp;
	set<string> intersect;


	minLen = min(norm.getMin(), rand.getMin());

	for(uint i = 0; i < maxInd; i++) 
	{
		//if the size of the two vectors are non-zero
		if(table[i].first.size()  && table[i].second.size()) 
		{
			count = 0;
			for(v_uint::iterator j = table[i].first.begin(); j != table[i].first.end(); j++) 
				for(v_uint::iterator k = table[i].second.begin(); k != table[i].second.end(); k++) 
				{
					for(uint l = 0; l < minLen; l++) 
						if(norm.getElement(*j)[l] != rand.getElement(*k)[l]) ++count;
					if(count <= TOLERANCE) 
					{
						if (jacc) intersect.insert(norm.getElement(*j).substr(0, minLen));
						else ++matches;
					}
				}
		}
	}
	if(jacc) return intersect.size();
	//otherwise
	return matches;
}

void
fillTable(pair<v_uint, v_uint> table[], const Seq & norm, const Seq & rand, const ulli seed) 
{
		uint minLen = min(norm.getMin(), rand.getMin());
		string n,r;
		if(norm.getSize() != rand.getSize())
		{
				cerr << "norm and rand size mismatch" << endl;
				exit(1);
		}
		v_uint hashKeyIdx = generateRand(HASH_LEN, minLen, seed);
		uint hashNorm, hashRand;
		/* build the table */
		//iterate through the norm and rand strings
		for(uint i = 0; i < norm.getSize(); ++i)
		{
				//these are the two strings to be inserted into the hash table
				n = norm.getElement(i);
				r = rand.getElement(i);
				hashNorm = hashRand = 0;
				for(uint j = 0; j < HASH_LEN; j++)
				{
						//build the keys for both the normal and random strings
						//TODO: Ensure that this is working properly
						hashNorm |= convert(n[hashKeyIdx[j]]) << ((HASH_LEN - j - 1) * 2);
						hashRand |= convert(r[hashKeyIdx[j]]) << ((HASH_LEN - j - 1) * 2);
				}
				//TODO: Make sure this logic is correct
				//after they've been built, index into the table with those hashed values
				//and insert the index of the current string in question from the norm
				//structure
				table[hashNorm].first.push_back(i);
				//and do the same for the rand structure
				table[hashRand].second.push_back(i);
		}
}

