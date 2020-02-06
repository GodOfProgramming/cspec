#include "cspec.hpp"

using namespace cspec;

Eval(spec1)
{
  Describe("A description", [] {
    Context("ARGV init", [] {
      It("passes", [] {
        Expect(ARGV.size()).toEqual((unsigned int)1);
      });
    });
    Context("ENV init", [] {
      It("passes", [] {
        Expect(ENV.size() > (unsigned int)1).toEqual(true);
      });
    });

    Context("A Context", [] {
      It("Does something", [] {
        Expect(1).toEqual(1);
        Expect(2).notToEqual(3);
      });
    });

    Context("Another test", [] {
      It("Fails", [] {
        Expect("foo").toEqual("foo");
        Expect("thing").notToEqual("not thing");
      });
    });

    Context("String tests", [] {
      char* str1 = nullptr;
      char* str2 = nullptr;
      char* str3 = nullptr;

      BeforeEach([&] {
        str1 = new char[6];
        str2 = new char[6];
        str3 = new char[6];
        memcpy(str1, "hello", sizeof(char) * 6);
        memcpy(str2, "hello", sizeof(char) * 6);
        memcpy(str3, "world", sizeof(char) * 6);
      });

      AfterEach([&] {
        delete[] str1;
        delete[] str2;
        delete[] str3;
      });

      It("strings are identical but not the same address", [&] {
        Expect(str1).toEqual(str2);
        Expect(str1).toEqual("hello");
        Expect("hello").toEqual(str2);
        Expect(str1).notToEqual(str3);
        Expect(str1).notToEqual("world");
        Expect("world").notToEqual(str2);
        Expect((size_t)&str1[0]).notToEqual((size_t)&str2[0]);
      });
    });
  });
}

Eval(spec2)
{
  Describe("A description in another test", [] {
    Context("A second context", [] {
      It("Does something again", [] {
        Expect(4).toEqual(4);
        Expect('a').notToEqual(true);
        Expect(0).toEqual('\0');
      });
    });
  });

  Describe("ranges", [] {
    It("works", [] {
      Expect(5).toBe().between(1, 10);
      Expect(5).toBe().between(10, 1);
      Expect(5).notToBe().between(10, 20);
      Expect(5).notToBe().between(20, 10);
    });
  });
}
