#include "cspec/cspec.hpp"

int main(int argc, char* argv[])
{
  return cspec::run_tests(argc, argv) ? 0 : 1;
}