#pragma once
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

namespace cspec
{
  std::string demangle(const char* name);

  template <typename T>
  std::string type(const T& t);

  inline std::string demangle(const char* name)
  {
    int status = 0;
    std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};

    return (status == 0) ? res.get() : name;
  }

  template <typename T>
  inline std::string type(const T& t)
  {
    return demangle(typeid(t).name());
  }
}  // namespace cspec

