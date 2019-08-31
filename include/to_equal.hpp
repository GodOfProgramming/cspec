#pragma once
#include <string.h>

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    struct ToEqual {
      bool operator()(E& expectation, V& value) {
        return expectation == value;
      }
    };

    /* <char*, char*> */
    template <>
    struct ToEqual<char*, char*> {
      bool operator()(char*& expectation, char*& value) {
        return strcmp(expectation, value) == 0;
      }
    };

    /* <char*, const char*> */
    template <>
    struct ToEqual<char*, const char*> {
      bool operator()(char*& expectation, const char*& value) {
        return strcmp(expectation, value) == 0;
      }
    };

    /* <const char*, char*> */
    template <>
    struct ToEqual<const char*, char*> {
      bool operator()(const char*& expectation, char*& value) {
        return strcmp(expectation, value) == 0;
      }
    };

    /* <const char*, const char*> */
    template <>
    struct ToEqual<const char*, const char*> {
      bool operator()(const char*& expectation, const char*& value) {
        return strcmp(expectation, value) == 0;
      }
    };
  }  // namespace matchers
}  // namespace cspec

