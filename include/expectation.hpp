#pragma once
#include <iomanip>
#include "console.hpp"
#include "exceptions.hpp"

#define Expect(expectation) cspec::_Expect_(expectation)

namespace cspec {
  extern bool gInItBlock;
  extern bool gItFailed;

  template <typename E>
  class Expectation {
    public:
      Expectation(E expectation) : mExpectation(expectation) {}

      template <typename V>
      void toEqual(V value) {
	toEqual(value,
	  console.setOpt<Console::Mod::FG_Cyan>(),
	  "\nExpectation Failed\n  ",
	  console.setOpt<Console::Mod::FG_Reset>(),
	  "Expected ", 
	  mExpectation, 
	  " to equal ", 
	  value, '\n', '\n'
	);
      }

      template <typename V, typename... Args>
	void toEqual(V value, Args&& ...args) 
	{
	  if (mExpectation != value) 
	  {
	    console.write(args...);
	    gItFailed = true;
	  }
	}

      template <typename V, typename... Args>
	void toContain(V value, Args&& ...args) 
	{
	  for (auto& element : mExpectation) 
	  {
	    if (element == value) 
	    {
	      return;
	    }
	  }

	  gItFailed = true;
	}

    private:
      E mExpectation;
  };

  template <typename T>
  Expectation<T> _Expect_(T expectation) 
  {
    if (!gInItBlock) 
    {
      throw InvalidExpectationException();
    }
    return Expectation<T>(expectation);
  }
}

