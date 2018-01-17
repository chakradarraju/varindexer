
#include "common/index.h"

#include <fstream>

namespace common {

Index ReadIndexOrDie(const std::string& index_path) {
  std::ifstream f(index_path);
  Index index;
  if (!index.ParseFromIstream(&f)) {
    std::cout << "Failed parsing index proto from " << index_path << std::endl;
    exit(1);
  }
  return index;
}

}  // namespace common
