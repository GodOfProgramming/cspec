#include "to_equal.hpp"
#include <string.h>

/* toEqual() specializations */

namespace cspec {
  namespace matchers {
    /* <char*, char*> */
    template <>
    bool toEqual(char* expectation, char* value) {
      return strcmp(expectation, value) == 0;
    }

    /* <const char*, const char*> */
    template <>
    bool toEqual(const char* expectation, const char* value) {
      return strcmp(expectation, value) == 0;
    }

    /* <char*, const char*> */
    template <>
    bool toEqual(char* expectation, const char* value) {
      return strcmp(expectation, value) == 0;
    }

    /* <const char*, char*> */
    template <>
    bool toEqual(const char* expectation, char* value) {
      return strcmp(expectation, value) == 0;
    }
  }  // namespace matchers
}  // namespace cspec
