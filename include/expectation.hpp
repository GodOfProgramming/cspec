#pragma once
#include "misc.hpp"
#include "matchers.hpp"
#include "string.h"

namespace cspec
{
    extern bool gInItBlock;
    extern bool gItFailed;

    /* Can also be specialized if needed and won't break anything as long as you follow similar logic */
    template <typename E>
    class Expectation
    {
       public:
        Expectation(E expectation, const char* file, int line) : mExpectation(expectation), mFile(file), mLine(line)
        {}

        virtual ~Expectation() = default;

        template <typename V, typename... Args>
        void toEqual(V value, Args&&... args)
        {
            matchers::ToEqual<E, V> matcher;
            checkResult(matcher(mExpectation, value), matcher.Message, '\n', '\n', args...);
        }

        template <typename V, typename... Args>
        void notToEqual(V value, Args&&... args)
        {
            matchers::NotToEqual<E, V> matcher;
            checkResult(matcher(mExpectation, value), matcher.Message, '\n', '\n', args...);
        }

        template <typename V, typename... Args>
        void toContain(V value, Args&&... args)
        {
            matchers::ToContain<E, V> matcher;
            checkResult(matcher(mExpectation, value), matcher.Message, '\n', '\n', args...);
        }

        template <typename V, typename... Args>
        void notToContain(V value, Args&&... args)
        {
            matchers::NotToContain<E, V> matcher;
            checkResult(matcher(mExpectation, value), matcher.Message, '\n', '\n', args...);
        }

       private:
        E mExpectation;
        const char* mFile;
        int mLine;

        template <typename... Args>
        void checkResult(bool res, Args&&... args)
        {
            if (!res) {
                capture('\n', mFile, " (", mLine, "): ", "\x1b[31m", "Evaluation Failed\n\t", "\x1b[m", args...);
                gItFailed = true;
            }
        }
    };
}  // namespace cspec
