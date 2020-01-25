#pragma once
#include <string>
#include <sstream>

namespace cspec {
  namespace matchers {
    template <typename V>
    inline std::string NotToContainDefaultMessage(V& value) {
      std::stringstream msg;
      msg << "Expected a container not to contain " << value;
      return msg.str();
    }

    /* Uses the for (element : container) {} syntax to support anything iterable */
    template <typename E, typename V>
    struct NotToContain {
      bool operator()(E& expectation, V& value) {
        for (auto& element : expectation) {
          if (element == value) {
            return false;
          }
        }
        Message = NotToContainDefaultMessage(value);
        return true;
      }

      std::string Message;
    };
  }  // namespace matchers
}  // namespace cspec
