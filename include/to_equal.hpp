#pragma once

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    bool toEqual(E expectation, V value) {
      return expectation == value;
    }

    extern template <>
    bool toEqual(char*, char*);

    extern template <>
    bool toEqual(const char*, const char*);

    extern template <>
    bool toEqual(char*, const char*);

    extern template <>
    bool toEqual(const char*, char*);
  }  // namespace matchers
}  // namespace cspec

