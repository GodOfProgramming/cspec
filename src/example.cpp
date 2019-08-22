#include "console.hpp"
#include "spec.hpp"
#include "stdio.h"

BeginSpec(spec1)

Describe("A description", [] {
  BeforeEach([] {
    console.write("In Desc BE", '\n');
  });

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

