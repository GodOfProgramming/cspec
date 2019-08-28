#pragma once
#include <stdexcept>

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
  }  // namespace matchers
}  // namespace cspec

