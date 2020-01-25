#pragma once
#include <string.h>

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    struct NotToEqual {
      bool operator()(E& expectation, V& value) {
        return expectation != value;
      }
    };

    /* <char*, char*> */
    template <>
    struct NotToEqual<char*, char*> {
      bool operator()(char*& expectation, char*& value) {
        return strcmp(expectation, value) != 0;
      }
    };

    /* <char*, const char*> */
    template <>
    struct NotToEqual<char*, const char*> {
      bool operator()(char*& expectation, const char*& value) {
        return strcmp(expectation, value) != 0;
      }
    };

    /* <const char*, char*> */
    template <>
    struct NotToEqual<const char*, char*> {
      bool operator()(const char*& expectation, char*& value) {
        return strcmp(expectation, value) != 0;
      }
    };

    /* <const char*, const char*> */
    template <>
    struct NotToEqual<const char*, const char*> {
      bool operator()(const char*& expectation, const char*& value) {
        return strcmp(expectation, value) != 0;
      }
    };
  }  // namespace matchers
}  // namespace cspec
