#pragma once
#include "misc.hpp"
#include "evaluate.hpp"
#include "string.h"

namespace cspec
{
    extern bool gInItBlock;
    extern bool gItFailed;

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
            EvalHelper<E, V> helper(mExpectation, value);
            checkResult(helper.EvaluateEq(), helper.MessageEq(), args...);
        }

        template <typename V, typename... Args>
        void notToEqual(V value, Args&&... args)
        {
            EvalHelper<E, V> helper(mExpectation, value);
            checkResult(helper.EvaluateNeq(), helper.MessageNeq(), args...);
        }

        template <typename V, typename... Args>
        void toContain(V value, Args&&... args)
        {
            EvalHelper<E, V> helper(mExpectation, value);
            checkResult(helper.EvaluateCon(), helper.MessageCon(), args...);
        }

        template <typename V, typename... Args>
        void notToContain(V value, Args&&... args)
        {
            EvalHelper<E, V> helper(mExpectation, value);
            checkResult(helper.EvaluateNcon(), helper.MessageNcon(), args...);
        }

       private:
        E mExpectation;
        const char* mFile;
        int mLine;

        template <typename... Args>
        void checkResult(bool res, std::string failure_message, Args&&... args)
        {
            if (!res) {
                capture('\n', mFile, " (", mLine, "): ", "\x1b[31m", "Evaluation Failed\n\t", "\x1b[m", failure_message, '\n');
                if (sizeof...(args) > 0) {
                    capture("\tMessage: ", args..., '\n');
                }
                gItFailed = true;
            }
        }
    };
}  // namespace cspec
