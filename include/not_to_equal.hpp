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
  }  // namespace matchers
}  // namespace cspec

