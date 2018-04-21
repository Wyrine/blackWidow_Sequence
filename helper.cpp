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
generateRand(uint size, uint n)
{
		v_uint rv;
		bool checkInit[n];

		memset(checkInit, 0, n*sizeof(bool));
		srand(RANDOM_SEED);

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
threadWork(const Seq & norm, const Seq & rand, const ulli maxInd, double myRes[])
{
		//table[i].first := vector of indices into norm
		//table[i].second := vector of indices into rand
		pair<v_uint, v_uint> table[maxInd];
		fillTable(table, norm, rand, maxInd);

		/* table should now be filled with the hashes, now generate results */

}

void
fillTable(pair<v_uint, v_uint> table[], const Seq & norm, const Seq & rand, 
				const ulli maxInd)
{
		v_uint hashKeyIdx = generateRand(HASH_LEN, maxInd);
		/* build the table */
}
