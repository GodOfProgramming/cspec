#include "Spec.hpp"
#include "stdio.h"

Begin(Spec_Example_Test);
Describe("A description", []() -> void {
  Context("A Context", []() -> void {
    It("Does something", []() -> void {
      Expect(1).toEqual(1);
      Expect(2).toEqual(3);
    });
  });

  Context("Another test", []() -> void {
    It("Fails", []() -> void {
      Expect("foo").toEqual("foo");
    });
  });
});
End();

Begin(A_Second_Example_Test);
Describe("A second description", []() -> void {
  Context("A second context", []() -> void {
    It("Does something again", []() -> void {
      Expect(4).toEqual(4);
      Expect('a').toEqual('b');
    });
  });
});
End();

