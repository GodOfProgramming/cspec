#include "cspec.hpp"

Eval(spec3)
{
    Describe("A second spec", [] {
        It("Fails so I can see the output", [] {
            auto a = "foo";
            auto b = "bar";
            Expect(a).toEqual(b);
	    Expect(b).toEqual(a);
        });

	Expect("this should trigger a InvalidExpectationException").toEqual("");
    });
}