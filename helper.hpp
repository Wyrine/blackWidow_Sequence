#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include <climits>

typedef unsigned int uint;
#define TABLES_PER_THREAD 1
//#define MAX_INT 1000000000000000000l

uint convert(const char bp);
std::vector<std::string> openAndReadFile(std::string, int &);
