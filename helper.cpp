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
