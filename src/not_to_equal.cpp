#include "not_to_equal.hpp"
#include <string.h>

/* notToEqual() specializations */

namespace cspec {
  namespace matchers {
    /* <char*, char*> */
    template <>
    bool notToEqual(char* expectation, char* value) {
      return strcmp(expectation, value) != 0;
    }

    /* <const char*, const char*> */
    template <>
    bool notToEqual(const char* expectation, const char* value) {
      return strcmp(expectation, value) != 0;
    }

    /* <char*, const char*> */
    template <>
    bool notToEqual(char* expectation, const char* value) {
      return strcmp(expectation, value) != 0;
    }

    /* <const char*, char*> */
    template <>
    bool notToEqual(const char* expectation, char* value) {
      return strcmp(expectation, value) != 0;
    }
  }
}  // namespace cspec

