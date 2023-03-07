// utils.cpp
// ~~~~~~~~~
// Util implementations
#include "utils.h"
#include <fstream>
#include <string>

const char *readFileIntoBuffer(const char *fileName) {
  std::ifstream in(fileName);
  std::string contents((std::istreambuf_iterator<char>()),
                       std::istreambuf_iterator<char>());
  const char *addy = contents.c_str();
  return addy;
}
