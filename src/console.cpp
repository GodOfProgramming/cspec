#include "console.hpp"

#define CODE_FORGROUND_RESET "\x1b[39m"
#define CODE_FORGROUND_BLACK "\x1b[30m"
#define CODE_FORGROUND_RED "\x1b[31m"
#define CODE_FORGROUND_GREEN "\x1b[32m"
#define CODE_FORGROUND_YELLOW "\x1b[33m"
#define CODE_FORGROUND_BLUE "\x1b[34m"
#define CODE_FORGROUND_MAGENTA "\x1b[35m"
#define CODE_FORGROUND_CYAN "\x1b[36m"
#define CODE_FORGROUND_WHITE "\x1b[37m"

#define CODE_BACKGROUND_RESET "\x1b[49m"
#define CODE_BACKGROUND_BLACK "\x1b[40m"
#define CODE_BACKGROUND_RED "\x1b[41m"
#define CODE_BACKGROUND_GREEN "\x1b[42m"
#define CODE_BACKGROUND_YELLOW "\x1b[43m"
#define CODE_BACKGROUND_BLUE "\x1b[44m"
#define CODE_BACKGROUND_MAGENTA "\x1b[45m"
#define CODE_BACKGROUND_CYAN "\x1b[46m"
#define CODE_BACKGROUND_WHITE "\x1b[47m"

#define CODE_FONTSTYLE_BOLD "\x1b[1m"
#define CODE_FONTSTYLE_FAINT "\x1b[2m"
#define CODE_FONTSTYLE_ITALIC "\x1b[3m"
#define CODE_FONTSTYLE_UNDERLINE "\x1b[4m"
#define CODE_FONTSTYLE_UNDERLINE_OFF "\x1b[24m"
#define CODE_FONTSTYLE_CROSSEDOUT "\x1b[9m"
#define CODE_FONTSTYLE_CROSSEDOUT_OFF "\x1b[29m"

#define CODE_MISC_FULLRESET "\x1b[m"
#define CODE_MISC_SLOWBLINK "\x1b[5m"
#define CODE_MISC_BLINK_OFF "\x1b[25m"

namespace cspec {
  Console console;

  /* Forground */
  template <>
  struct Console::tostr<Console::Mod::FG_Reset> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Reset>::value = CODE_FORGROUND_RESET;

  template <>
  struct Console::tostr<Console::Mod::FG_Black> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Black>::value = CODE_FORGROUND_BLACK;

  template <>
  struct Console::tostr<Console::Mod::FG_Red> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Red>::value = CODE_FORGROUND_RED;

  template <>
  struct Console::tostr<Console::Mod::FG_Green> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Green>::value = CODE_FORGROUND_GREEN;

  template <>
  struct Console::tostr<Console::Mod::FG_Yellow> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Yellow>::value = CODE_FORGROUND_YELLOW;

  template <>
  struct Console::tostr<Console::Mod::FG_Blue> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Blue>::value = CODE_FORGROUND_BLUE;

  template <>
  struct Console::tostr<Console::Mod::FG_Magenta> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Magenta>::value = CODE_FORGROUND_MAGENTA;

  template <>
  struct Console::tostr<Console::Mod::FG_Cyan> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_Cyan>::value = CODE_FORGROUND_CYAN;

  template <>
  struct Console::tostr<Console::Mod::FG_White> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FG_White>::value = CODE_FORGROUND_WHITE;

  /* Background */
  template <>
  struct Console::tostr<Console::Mod::BG_Reset> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Reset>::value = CODE_BACKGROUND_RESET;

  template <>
  struct Console::tostr<Console::Mod::BG_Black> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Black>::value = CODE_BACKGROUND_BLACK;

  template <>
  struct Console::tostr<Console::Mod::BG_Red> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Red>::value = CODE_BACKGROUND_RED;

  template <>
  struct Console::tostr<Console::Mod::BG_Green> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Green>::value = CODE_BACKGROUND_GREEN;

  template <>
  struct Console::tostr<Console::Mod::BG_Yellow> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Yellow>::value = CODE_BACKGROUND_YELLOW;

  template <>
  struct Console::tostr<Console::Mod::BG_Blue> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Blue>::value = CODE_BACKGROUND_BLUE;

  template <>
  struct Console::tostr<Console::Mod::BG_Magenta> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Magenta>::value = CODE_BACKGROUND_MAGENTA;

  template <>
  struct Console::tostr<Console::Mod::BG_Cyan> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_Cyan>::value = CODE_BACKGROUND_CYAN;

  template <>
  struct Console::tostr<Console::Mod::BG_White> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::BG_White>::value = CODE_BACKGROUND_WHITE;

  /* Font styles */
  template <>
  struct Console::tostr<Console::Mod::FS_Bold> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_Bold>::value = CODE_FONTSTYLE_BOLD;

  template <>
  struct Console::tostr<Console::Mod::FS_Faint> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_Faint>::value = CODE_FONTSTYLE_FAINT;

  template <>
  struct Console::tostr<Console::Mod::FS_Italic> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_Italic>::value = CODE_FONTSTYLE_ITALIC;

  template <>
  struct Console::tostr<Console::Mod::FS_Underline> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_Underline>::value = CODE_FONTSTYLE_UNDERLINE;

  template <>
  struct Console::tostr<Console::Mod::FS_UnderlineOff> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_UnderlineOff>::value = CODE_FONTSTYLE_UNDERLINE_OFF;

  template <>
  struct Console::tostr<Console::Mod::FS_CrossedOut> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_CrossedOut>::value = CODE_FONTSTYLE_CROSSEDOUT;

  template <>
  struct Console::tostr<Console::Mod::FS_CrossedOutOff> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::FS_CrossedOutOff>::value = CODE_FONTSTYLE_CROSSEDOUT_OFF;

  /* Misc */
  template <>
  struct Console::tostr<Console::Mod::M_FullReset> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::M_FullReset>::value = CODE_MISC_FULLRESET;

  template <>
  struct Console::tostr<Console::Mod::M_SlowBlink> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::M_SlowBlink>::value = CODE_MISC_SLOWBLINK;

  template <>
  struct Console::tostr<Console::Mod::M_BlinkOff> {
    static const char* const value;
  };
  const char* const Console::tostr<Console::Mod::M_BlinkOff>::value = CODE_MISC_BLINK_OFF;
}  // namespace cspec
