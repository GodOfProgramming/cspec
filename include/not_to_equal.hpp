#pragma once

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    bool notToEqual(E expectation, V value) {
      return expectation != value;
    }

    extern template <>
    bool notToEqual(char*, char*);

    extern template <>
    bool notToEqual(const char*, const char*);

    extern template <>
    bool notToEqual(char*, const char*);

    extern template <>
    bool notToEqual(const char*, char*);
  }  // namespace matchers
}  // namespace cspec

