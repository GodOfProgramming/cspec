#include "spec.hpp"

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

BeginSpec(ClassSpec);

Describe("Foobar", [] {
  Foobar foo(1);
  Foobar bar(2);

  It("not equal", [&] { Expect(foo).notToEqual(bar); });

  BeforeEach([&] { bar.change(1); });

  It("equal", [&] { Expect(foo).toEqual(bar); });
});

EndSpec;
