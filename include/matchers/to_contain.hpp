#pragma once
#include <string>
#include <sstream>

namespace cspec {
  namespace matchers {
    template <typename V>
    inline std::string ToContainDefaultMessage(V& value) {
      std::stringstream msg;
      msg << "Expected a container to contain " << value;
      return msg.str();
    }

    /* Uses the for (element : container) {} syntax to support anything iterable */
    template <typename E, typename V>
    struct ToContain {
      bool operator()(E& expectation, V& value) {
        for (auto& element : expectation) {
          if (element == value) {
            return true;
          }
        }
        Message = ToContainDefaultMessage(value);
        return false;
      }

      std::string Message;
    };
  }  // namespace matchers
}  // namespace cspec
