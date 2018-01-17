
#include "common/file.h"

#include <fstream>
#include "common/index.pb.h"

namespace common {

using std::vector;
using std::string;

vector<string> GetFileContents(const string& text_input) {
  std::ifstream f(text_input);
  vector<string> result;
  while (!f.eof()) {
    string line;
    std::getline(f, line);
    if (line.size() > 0) result.push_back(line);
  }
  f.close();
  return result;
}

void WriteIndexTo(const common::Index& index, const string& index_path) {
  std::ofstream f(index_path);
  index.SerializeToOstream(&f);
  f.close();
}

}  // namespace common
