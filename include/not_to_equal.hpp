#pragma once
#include "matcher.hpp"

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    class NotToEqual : public Matcher<E, V> {
     public:
      NotToEqual(E& expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) const {
        return this->mExpectation != value;
      }
    };

    /* <char*, char*> */
    template <>
    class NotToEqual<char*, char*> : public Matcher<char*, char*> {
     public:
      NotToEqual(char*& expectation) : Matcher<char*, char*>(expectation) {
      }

      bool operator()(char* value) const {
        return strcmp(this->mExpectation, value) != 0;
      }
    };

    /* <const char*, const char*> */
    template <>
    class NotToEqual<const char*, const char*> : public Matcher<const char*, const char*> {
     public:
      NotToEqual(const char*& expectation) : Matcher<const char*, const char*>(expectation) {
      }

      bool operator()(const char* value) const {
        return strcmp(this->mExpectation, value) != 0;
      }
    };

    /* <char*, const char*> */
    template <>
    class NotToEqual<char*, const char*> : public Matcher<char*, const char*> {
     public:
      NotToEqual(char*& expectation) : Matcher<char*, const char*>(expectation) {
      }

      bool operator()(const char* value) const {
        return strcmp(this->mExpectation, value) != 0;
      }
    };

    /* <const char*, char*> */
    template <>
    class NotToEqual<const char*, char*> : public Matcher<const char*, char*> {
     public:
      NotToEqual(const char*& expectation) : Matcher<const char*, char*>(expectation) {
      }

      bool operator()(char* value) const {
        return strcmp(this->mExpectation, value) != 0;
      }
    };
  }  // namespace matchers
}  // namespace cspec

