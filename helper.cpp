#include "helper.hpp"

using namespace std;


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
