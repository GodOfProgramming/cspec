#include "spec.hpp"
#include "sstream"

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

std::ostream& operator<<(std::ostream& os, const Foobar& f) {
  return os << f.toString();
}

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

namespace cspec {
  namespace matchers {
    template <>
    class ToEqual<Test, Test> : public Matcher<Test, Test> {
     public:
      ToEqual(Test& expectation) : Matcher<Test, Test>(expectation) {
      }

      bool operator()(Test value) const {
        return mExpectation.equals(value);
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
