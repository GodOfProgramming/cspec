#pragma once

namespace cspec {
  namespace matchers {
    /* Uses the for (element : container) {} syntax to support anything iterable */
    template <typename E, typename V>
    struct ToContain {
      bool operator()(E& expectation, V& value) {
        for (auto& element : expectation) {
          if (element == value) {
            return true;
          }
        }
        return false;
      }
    };
  }  // namespace matchers
}  // namespace cspec
