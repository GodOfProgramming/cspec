#pragma once
#include <iostream>

namespace cspec {
  class Console {
   public:
    enum class Mod {
      /* Forground */
      FG_Reset,
      FG_Black,
      FG_Red,
      FG_Green,
      FG_Yellow,
      FG_Blue,
      FG_Magenta,
      FG_Cyan,
      FG_White,

      /* Background */
      BG_Reset,
      BG_Black,
      BG_Red,
      BG_Green,
      BG_Yellow,
      BG_Blue,
      BG_Magenta,
      BG_Cyan,
      BG_White,

      /* Font Style */
      FS_Bold,
      FS_Faint,
      FS_Italic,
      FS_Underline,
      FS_UnderlineOff,
      FS_CrossedOut,
      FS_CrossedOutOff,

      /* Misc */
      M_FullReset,
      M_SlowBlink,
      M_BlinkOff
    };

    Console() = default;

    template <Mod E>
    constexpr inline const char *setOpt() {
      return tostr<E>::value;
    }

    template <typename... Args>
    void write(Args &&... args) {
      ((std::cout << std::forward<Args>(args)), ...) << setOpt<Mod::M_FullReset>();
    }

   private:
    template <Mod E>
    struct tostr {
      static const char *const value;
    };
  };

  extern Console console;
}  // namespace cspec

