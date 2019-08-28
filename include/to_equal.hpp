#pragma once
#include <string.h>
#include "matcher.hpp"

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    class ToEqual : public Matcher<E, V> {
     public:
      ToEqual(E& expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) const {
        return this->mExpectation == value;
      }
    };

    /* ToEqual specializations */

    /* <char*, char*> */
    template <>
    class ToEqual<char*, char*> : public Matcher<char*, char*> {
     public:
      ToEqual(char* expectation) : Matcher<char*, char*>(expectation) {
      }

      bool operator()(char* value) const {
        return !strcmp(this->mExpectation, value);
      }
    };

    /* <const char*, const char*> */
    template <>
    class ToEqual<const char*, const char*> : public Matcher<const char*, const char*> {
     public:
      ToEqual(const char* expectation) : Matcher<const char*, const char*>(expectation) {
      }

      bool operator()(const char* value) const {
        return !strcmp(this->mExpectation, value);
      }
    };
  }  // namespace matchers
}  // namespace cspec

