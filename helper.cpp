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
				if((count + 2) % 4 == 0) 
						rv.addSeq(line);
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
		}
		return rv;
}

vector<uint>
generateRand(uint size, uint n)
{
		vector<uint> rv;
		bool checkInit[n];

		memset(checkInit, 0, n*sizeof(uint));
		srand(RANDOM_SEED);

		for(uint i = 0; i < size; ++i)
		{
				uint tmp = rand() % n;

				while(checkInit[tmp]) tmp = rand() % n;
				checkInit[tmp] = true;
				rv.push_back(tmp);
		}
		return rv;
}
