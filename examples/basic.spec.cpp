#include "spec.hpp"

BeginSpec(spec1);

Describe("A description", [] {
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

    BeforeEach([&] {
      str1 = new char[6];
      str2 = new char[6];
      memcpy(str1, "hello", sizeof(char) * 6);
      memcpy(str2, "hello", sizeof(char) * 6);
    });

    AfterEach([&] {
      delete[] str1;
      delete[] str2;
    });

    It("strings are identical but not the same address", [&] {
      console.write("\n\n\n\n\n\n");
      Expect(str1).toEqual(str2);
      // Expect(str1).test("AAAAAAAAAAAAA");
      cspec::Expectation<char*, cspec::ExpectationOverride::CharChild>(str1).toEqual(str2);
      // Expect(&str1[0]).notToEqual(&str2[0]);
      console.write("\n\n\n\n\n\n");
    });
  });
});

EndSpec();

BeginSpec(spec2);

Describe("A description in another test", [] {
  Context("A second context", [] {
    It("Does something again", [] {
      Expect(4).toEqual(4);
      Expect('a').notToEqual(true);
      Expect(0).toEqual('\0');
    });
  });
});

EndSpec();
