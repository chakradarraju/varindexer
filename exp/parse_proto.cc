
#include <gflags/gflags.h>

#include "common/index.h"
#include "common/flags.h"

DEFINE_string(index_path, "", "Path to write index to.");

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  common::ReadIndexOrDie(common::GetFlagOrDie(FLAGS(index_path)));

  gflags::ShutDownCommandLineFlags();
  return 0;
}
