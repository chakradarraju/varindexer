#include <queue>
#include <iostream>

int main() {
  std::vector<int> v{1, 1, 2, 3, 4, 4};
  std::priority_queue<int> q(v.begin(), v.end());
  std::cout << q.size() << std::endl;
  return 0;
}
