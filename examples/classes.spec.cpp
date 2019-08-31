#include "spec.hpp"
#include "sstream"

// Used to demo usage of regular classes without specialization
class Foobar {
 public:
  Foobar(int id) : mId(id){};

  void change(int id) {
    this->mId = id;
  }

  bool operator==(const Foobar& other) {
    return this->mId == other.mId;
  }

  bool operator!=(const Foobar& other) {
    return !(*this == other);
  }

  std::string toString() const {
    std::stringstream ss;
    ss << "Foobar(" << mId << ")";
    return ss.str();
  }

 private:
  int mId;
};

// In the event an expectation fails, the expectation and value are
// cout-ed and thus need to be compatible with the << operator
std::ostream& operator<<(std::ostream& os, const Foobar& f) {
  return os << f.toString();
}

// Used for ToEqual specialization
class Test {
 public:
  Test(std::string str) : mStr(str) {
  }

  bool equals(const Test& other) {
    return this->mStr == other.mStr;
  }

  std::string toString() const {
    return mStr;
  }

 private:
  std::string mStr;
};

std::ostream& operator<<(std::ostream& os, const Test& t) {
  return os << t.toString();
}

/* This is how you overload the toEqual matcher (along with notToEqual, toContain, ...)
 * Files to look at for what matchers to overload:
 * to_equal.hpp,
 * not_to_equal.hpp,
 * to_contain.hpp,
 * not_to_contain.hpp
 */
namespace cspec {
  namespace matchers {
    template <>
    struct ToEqual<Test, Test> {
      bool operator()(Test expectation, Test value) {
        return expectation.equals(value);
      }
    };
  }  // namespace matchers
}  // namespace cspec

BeginSpec(ClassSpec);

Describe("Foobar", [] {
  Foobar foo(1);
  Foobar bar(2);

  It("not equal", [&] { Expect(foo).notToEqual(bar); });

  BeforeEach([&] { bar.change(1); });

  It("equal", [&] { Expect(foo).toEqual(bar); });
});

Describe("Test overload", [] {
  Test t1("foo");
  Test t2("foo");

  It("returns true", [&] { Expect(t1).toEqual(t2); });
});

EndSpec();
