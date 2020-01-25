#pragma once
#include <string.h>
#include <string>
#include <sstream>

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    inline std::string ToEqualDefaultMessage(E& expectation, V& value) {
      std::stringstream msg;
      msg << "Expected " << expectation << " to equal " << value;
      return msg.str();
    }

    template <typename E, typename V>
    struct ToEqual {
      bool operator()(E& expectation, V& value) {
        if (expectation == value) {
          return true;
        } else {
          Message = ToEqualDefaultMessage(expectation, value);
          return false;
        }
      }

      std::string Message;
    };

    /* <char*, char*> */
    template <>
    struct ToEqual<char*, char*> {
      bool operator()(char*& expectation, char*& value) {
        if (strcmp(expectation, value) == 0) {
          return true;
        } else {
          std::stringstream msg;
          msg << "Expected \"" << expectation << "\" to equal \"" << value << '"';
          Message = msg.str();
          return false;
        }
      }

      std::string Message;
    };

    /* <char*, const char*> */
    template <>
    struct ToEqual<char*, const char*> {
      bool operator()(char*& expectation, const char*& value) {
        if (strcmp(expectation, value) == 0) {
          return true;
        } else {
          std::stringstream msg;
          msg << "Expected \"" << expectation << "\" to equal \"" << value << '"';
          Message = msg.str();
          return false;
        }
      }

      std::string Message;
    };

    /* <const char*, char*> */
    template <>
    struct ToEqual<const char*, char*> {
      bool operator()(const char*& expectation, char*& value) {
        if (strcmp(expectation, value) == 0) {
          return true;
        } else {
          std::stringstream msg;
          msg << "Expected \"" << expectation << "\" to equal \"" << value << '"';
          Message = msg.str();
          return false;
        }
      }

      std::string Message;
    };

    /* <const char*, const char*> */
    template <>
    struct ToEqual<const char*, const char*> {
      bool operator()(const char*& expectation, const char*& value) {
        if (strcmp(expectation, value) == 0) {
          return true;
        } else {
          std::stringstream msg;
          msg << "Expected \"" << expectation << "\" to equal \"" << value << '"';
          Message = msg.str();
          return false;
        }
      }

      std::string Message;
    };

    /* <std::string, std::string> */
    template <>
    struct ToEqual<std::string, std::string> {
      bool operator()(std::string& expectation, std::string& value) {
        if (expectation == value) {
          return true;
        } else {
          std::stringstream msg;
          msg << "Expected \"" << expectation << "\" to equal \"" << value << '"';
          Message = msg.str();
          return false;
        }
      }

      std::string Message;
    };
  }  // namespace matchers
}  // namespace cspec
