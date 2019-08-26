#include "expectation.hpp"

namespace cspec {
  template <>
  class Expectation<char*, ExpectationOverride::CharChild> : public Expectation<char*, ExpectationOverride::CharBase> {
   public:
    Expectation(char* value) : Expectation<char*, ExpectationOverride::CharBase>(value) {
      console.write('\n', "In CharChild", '\n');
    }

    void toEqual(char* value) {
      console.write('\n', "In CharChild toEqual", '\n');
      toEqual(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected '",
          mExpectation,
          "' to equal '",
          value,
          '\'',
          '\n',
          '\n');
    }

    template <typename... Args>
    void toEqual(char* value, Args&&... args) {
      if (strcmp(mExpectation, value)) {
        gItFailed = true;
        console.write(args...);
      }
    }
  };

  template <>
  class Expectation<const char, ExpectationOverride::ConstCharChild>
      : public Expectation<const char*, ExpectationOverride::ConstCharBase> {
   public:
    Expectation(const char* expectation) : Expectation<const char*, ExpectationOverride::ConstCharBase>(expectation) {
      console.write('\n', "In ConstCharChild", '\n');
    }

    void toEqual(const char* value) {
      console.write('\n', "In ConstCharChild toEqual", '\n');
      toEqual(value,
          console.setOpt<Console::Mod::FG_Cyan>(),
          "\nExpectation Failed\n  ",
          console.setOpt<Console::Mod::FG_Reset>(),
          "Expected '",
          mExpectation,
          "' to equal '",
          value,
          '\'',
          '\n',
          '\n');
    }

    template <typename... Args>
    void toEqual(const char* value, Args&&... args) {
      if (strcmp(mExpectation, value)) {
        gItFailed = true;
        console.write(args...);
      }
    }
  };
}  // namespace cspec

