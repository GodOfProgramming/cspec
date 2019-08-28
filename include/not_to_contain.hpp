#pragma once
#include "matcher.hpp"

namespace cspec {
  namespace matchers {
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
