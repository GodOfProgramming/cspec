#pragma once
#include "misc.hpp"
#include "evaluate.hpp"
#include "string.h"
#include "failable.hpp"
#include "to_be.hpp"

namespace cspec
{
  extern bool gInItBlock;

  template <typename E>
  class Expectation: public Failable
  {
   public:
    Expectation(E expectation, const char* file, int line): mExpectation(expectation)
    {
      mFile = file;
      mLine = line;
    }
    virtual ~Expectation() = default;

    template <typename V, typename... Args>
    void toEqual(V value, Args&&... args)
    {
      EvalHelper<E, V> helper(mExpectation, value);
      checkResult(helper.EvaluateEq(), helper.MessageEq(), args...);
    }

    template <typename V, typename... Args>
    void notToEqual(V value, Args&&... args)
    {
      EvalHelper<E, V> helper(mExpectation, value);
      checkResult(helper.EvaluateNeq(), helper.MessageNeq(), args...);
    }

    template <typename V, typename... Args>
    void toContain(V value, Args&&... args)
    {
      EvalHelper<E, V> helper(mExpectation, value);
      checkResult(helper.EvaluateCon(), helper.MessageCon(), args...);
    }

    template <typename V, typename... Args>
    void notToContain(V value, Args&&... args)
    {
      EvalHelper<E, V> helper(mExpectation, value);
      checkResult(helper.EvaluateNcon(), helper.MessageNcon(), args...);
    }

    ToBe<E> toBe()
    {
      return ToBe<E>(mExpectation, mFile, mLine);
    }

    NotToBe<E> notToBe()
    {
      return NotToBe<E>(mExpectation, mFile, mLine);
    }

   private:
    E mExpectation;
  };

}  // namespace cspec
