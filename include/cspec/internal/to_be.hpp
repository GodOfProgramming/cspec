#pragma once
#include "failable.hpp"

#include <tuple>
#include <functional>

namespace cspec
{
  template <typename E>
  class ToBe: public Failable
  {
   public:
    ToBe(E& e, const char* file, int line)
    {
      mExpectation = &e;
      mFile = file;
      mLine = line;
    }
    ~ToBe() = default;

    template <typename T, typename... Args>
    void between(T a, T b, Args&&... args)
    {
      auto bounds = std::make_tuple(a, b);
      EvalHelper<E, std::tuple<T, T>> helper(*mExpectation, bounds);
      checkResult(helper.EvaluateBetween(), helper.MessageBetween(), args...);
    }

   private:
    E* mExpectation;
  };

  template <typename E>
  class NotToBe: public Failable
  {
   public:
    NotToBe(E& e, const char* file, int line)
    {
      mExpectation = &e;
      mFile = file;
      mLine = line;
    }
    ~NotToBe() = default;

    template <typename T, typename... Args>
    void between(T a, T b, Args&&... args)
    {
      auto bounds = std::make_tuple(a, b);
      EvalHelper<E, std::tuple<T, T>> helper(*mExpectation, bounds);
      checkResult(helper.EvaluateNotBetween(), helper.MessageNotBetween(), args...);
    }

   private:
    E* mExpectation;
  };
}  // namespace cspec

