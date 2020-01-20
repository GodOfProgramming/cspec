#include "spec.hpp"

BeginSpec(spec3);
Describe("A second spec", [] { It("Fails so I can see the output", [] { Expect("foo").toEqual("bar"); }); });
EndSpec();
