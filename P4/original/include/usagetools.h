#include <iostream>
#include <string>
#include <stdexcept>

struct Options {
  unsigned tableSize;
  std::string dispersionFunction;
  std::string hashType;
  unsigned blockSize;
  std::string explorationFunction;
};

void Usage();
Options ParseArguments(int argc, char* argv[]);