#include "expectation.hpp"

namespace cspec {
  template <>
  Expectation<const char*>::toEqual(const char* value) {
    toEqual(value,
        console.setOpt<Console::Mod::FG_Cyan>(),
        "\nExpectation Failed\n  ",
        console.setOpt<Console::Mod::FG_Reset>(),
        "Expected ",
        mExpectation,
        " to equal ",
        value,
        '\n',
        '\n');
  }
}  // namespace cspec

