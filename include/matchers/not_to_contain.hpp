#pragma once

namespace cspec {
  namespace matchers {
    /* Uses the for (element : container) {} syntax to support anything iterable */
    template <typename E, typename V>
    struct NotToContain {
      bool operator()(E& expectation, V& value) {
        for (auto& element : expectation) {
          if (element == value) {
            return false;
          }
        }
        return true;
      }
    };
  }  // namespace matchers
}  // namespace cspec
