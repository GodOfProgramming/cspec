#include <unordered_map>
#include <vector>
#include "cspec.hpp"

BeginSpec(contains_spec);

Describe("Contain expectation", [] {
  std::vector<int> container;

  BeforeEach([&] {
    container.push_back(1);
    container.push_back(2);
    container.push_back(3);
  });

  AfterEach([&] { container.resize(0); });

  Context("Element Present", [&] {
    BeforeEach([&] { container.push_back(4); });

    It("Does contains 4", [&] { Expect(container).toContain(4); });
  });

  Context("Element not present", [&] { It("Doesn't contain 4", [&] { Expect(container).notToContain(4); }); });
});

EndSpec();
