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
});

EndSpec;

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

EndSpec;
