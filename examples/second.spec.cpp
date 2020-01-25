#include "spec.hpp"

BeginSpec(spec3);
Describe("A second spec", [] {
  It("Fails so I can see the output", [] {
    auto a = "foo";
    auto b = "bar";
    Expect(a).toEqual(b);
  });

  It("Fails again to see output", [] {
    std::string a = "foo";
    std::string b = "bar";
    Expect(a).toEqual(b);
  });
});
EndSpec();
