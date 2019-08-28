#pragma once
#include "matcher.hpp"

namespace cspec {
  namespace matchers {
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
  }  // namespace matchers
}  // namespace cspec

