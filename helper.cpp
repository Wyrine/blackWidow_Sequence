#include "helper.hpp"

using namespace std;

vector<string> 
openAndReadFile(string fname, int &minLen)
{
		ifstream f(fname);
		if(!f.is_open())
		{
				cerr << "you suck" << endl;
				exit(1);
		}
		string line;
		vector<string> rv;
		int count = 1;
		while(getline(f, line))
		{
				if((count + 2) % 4 == 0) 
				{
						if(line.length() < minLen)
								minLen = line.length();
						rv.push_back(line);
						cout << line << endl;
				}
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
