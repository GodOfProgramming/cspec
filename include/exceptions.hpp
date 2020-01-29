#pragma once

namespace cspec
{
    class InvalidExpectationException
    {
       public:
        inline InvalidExpectationException(const char* file, int line) : File(file), Line(line)
        {}

	const char* File;
	int Line;
    };
}  // namespace cspec
