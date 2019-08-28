#pragma once
#include <stdexcept>
#include <string.h>
#include "console.hpp"

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    class Matcher {
     public:
      virtual ~Matcher() {
      }

      bool operator()(V value) const {
        throw std::runtime_error("Invalid Matcher");
      };

     protected:
      Matcher(E& expectation) : mExpectation(expectation) {
      }

      E& mExpectation;
    };

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
    template <>
    class ToEqual<char*, char*> : public Matcher<char*, char*> {
     public:
      ToEqual(char* expectation) : Matcher<char*, char*>(expectation) {
      }

      bool operator()(char* value) const {
        return !strcmp(this->mExpectation, value);
      }
    };

    template <>
    class ToEqual<const char*, const char*> : public Matcher<const char*, const char*> {
     public:
      ToEqual(const char* expectation) : Matcher<const char*, const char*>(expectation) {
      }

      bool operator()(const char* value) const {
        return !strcmp(this->mExpectation, value);
      }
    };

    template <typename E, typename V>
    class NotToEqual : public Matcher<E, V> {
     public:
      NotToEqual(E& expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) const {
        return this->mExpectation != value;
      }
    };

    template <typename E, typename V>
    class ToContain : public Matcher<E, V> {
     public:
      ToContain(E& expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) const {
        for (auto& element : this->mExpectation) {
          if (element == value) {
            return true;
          }
        }
        return false;
      }
    };

    template <typename E, typename V>
    class NotToContain : public Matcher<E, V> {
     public:
      NotToContain(E& expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) const {
        for (auto& element : this->mExpectation) {
          if (element == value) {
            return false;
          }
        }

        return true;
      }
    };
  }  // namespace matchers
}  // namespace cspec

