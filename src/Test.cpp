#include "Spec.hpp"
#include "stdio.h"

Begin(Spec_Example_Test)
Describe("A description", []() -> void {
    Context("A Context", []() -> void {
	It("Does something", []() -> void {
	    Expect(1).toEqual(1);
	    Expect(2).toEqual(3);
	});
    });
});
End()
