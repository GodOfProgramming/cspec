#pragma once

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    bool notToContain(E expectation, V value) {
      for (auto& element : expectation) {
        if (element == value) {
          return false;
        }
      }
      return true;
    }
  }  // namespace matchers
}  // namespace cspec
