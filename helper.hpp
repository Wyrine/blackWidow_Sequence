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

uint convert(const char bp);
std::vector<std::string> openAndReadFile(std::string, int &);
std::vector<uint> generateRand(uint, uint);
