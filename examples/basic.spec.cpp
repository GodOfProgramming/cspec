#include "console.hpp"
#include "spec.hpp"
#include "stdio.h"
#include "sstream"

class Foobar {
  public:
    Foobar(int id) : mId(id) { };

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

std::ostream &operator<<(std::ostream &os, const Foobar& f) { 
  return os << f.toString();
}

BeginSpec(spec1)

Describe("Foobar", [] {
  BeforeEach([] {
    console.write("About to run foobar test", '\n');
  });

  AfterEach([] {
    console.write("Ran foobar test", '\n');
  });

  Context("Passing tests", [] {
    It("passes", [] {
      Expect(1).toEqual(1);
    });

    It("passes", [] {
      Expect('A').toEqual(65);
    });
  });

  Foobar foo(1);
  Foobar bar(2);

  It("Fails", [&] {
    Expect(foo).toEqual(bar);
  });

  BeforeEach([&] {
    bar.change(1);
  });

  It("Passes", [&] {
    Expect(foo).toEqual(bar);
  });
});

Describe("A description", [] {
  Context("A Context", [] {
    It("Does something", [] {
      Expect(1).toEqual(1);
      Expect(2).toEqual(3);
    });
  });

  Context("Another test", [] {
    It("Fails", [] {
      Expect("foo").toEqual("foo");
      Expect("thing").toEqual("not thing");
    });
  });
});

EndSpec

BeginSpec(spec2)

Describe("A description in another test", [] {
  Context("A second context", [] {
    It("Does something again", [] {
      Expect(4).toEqual(4);
      Expect('a').toEqual(true);
    });
  });
});

EndSpec

