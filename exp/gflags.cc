#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(message, "Hello world!", "Message to print");

static bool IsNonEmptyMessage(const char *flagname, const std::string &value)
{
  return value[0] != '\0';
}
DEFINE_validator(message, &IsNonEmptyMessage);

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::cout << FLAGS_message << std::endl;
  gflags::ShutDownCommandLineFlags();
  return 0;
}
