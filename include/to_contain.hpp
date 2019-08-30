#pragma once

namespace cspec {
  namespace matchers {
    /* Uses a for (element : container) {} syntax to support anything iterable */
    template <typename E, typename V>
    bool toContain(E expectation, V value) {
      for (auto& element : expectation) {
        if (element == value) {
          return true;
        }
      }
      return false;
    }
  }  // namespace matchers
}  // namespace cspec

