#pragma once
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

namespace
{
    template <typename... Args>
    inline std::string FmtHelper(Args&&... args)
    {
        std::stringstream ss;
        ((ss << std::forward<Args>(args)), ...);
        return ss.str();
    }
}  // namespace

namespace cspec
{
    template <typename E, typename V>
    struct EvalHelper
    {
        EvalHelper(E& e, V& v) : e(e), v(v)
        {}

        bool EvaluateEq();
        bool EvaluateNeq();
        bool EvaluateCon();
        bool EvaluateNcon();

        std::string MessageEq();
        std::string MessageNeq();
        std::string MessageCon();
        std::string MessageNcon();

        E& e;  // expectation
        V& v;  // value
    };

    template <typename E, typename V>
    inline std::string EvalHelper<E, V>::MessageEq()
    {
        return FmtHelper("Expected ", e, " to equal ", v, '\n');
    }

    template <typename E, typename V>
    inline std::string EvalHelper<E, V>::MessageNeq()
    {
        return FmtHelper("Expected ", e, " not to equal ", v, '\n');
    }

    template <typename E, typename V>
    inline std::string EvalHelper<E, V>::MessageCon()
    {
        return FmtHelper("Expected a container to contain ", v, '\n');
    }

    template <typename E, typename V>
    inline std::string EvalHelper<E, V>::MessageNcon()
    {
        return FmtHelper("Expected a container not to contain ", v, '\n');
    }

    template <typename E, typename V>
    inline bool EvalHelper<E, V>::EvaluateEq()
    {
        return e == v;
    }

    template <typename E, typename V>
    inline bool EvalHelper<E, V>::EvaluateNeq()
    {
        return e != v;
    }

    template <typename E, typename V>
    inline bool EvalHelper<E, V>::EvaluateCon()
    {
        for (auto& el : e) {
            if (el == v) {
                return true;
            }
        }
        return false;
    }

    template <typename E, typename V>
    inline bool EvalHelper<E, V>::EvaluateNcon()
    {
        return !EvaluateCon();
    }

    /********************************************************************/
    /*				Specializations				*/
    /********************************************************************/

    /********************************************************************/
    /*				Messages				*/
    /********************************************************************/

    // Eq
    
    template <>
    inline std::string EvalHelper<char*, char*>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<char*, const char*>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<const char*, char*>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<const char*, const char*>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<std::string, std::string>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<std::string, char*>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<char*, std::string>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<std::string, const char*>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<const char*, std::string>::MessageEq()
    {
        return FmtHelper("Expected '", e, "' to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<bool, bool>::MessageEq()
    {
        return FmtHelper("Expected ", e ? "true" : "false", " to equal ", v ? "true" : "false", '\n');
    }

    // Neq

    template <>
    inline std::string EvalHelper<char*, char*>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<char*, const char*>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<const char*, char*>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<const char*, const char*>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<std::string, std::string>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<std::string, char*>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<char*, std::string>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<std::string, const char*>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<const char*, std::string>::MessageNeq()
    {
        return FmtHelper("Expected '", e, "' not to equal '", v, "'\n");
    }

    template <>
    inline std::string EvalHelper<bool, bool>::MessageNeq()
    {
        return FmtHelper("Expected ", e ? "true" : "false", " not to equal ", v ? "true" : "false", '\n');
    }

    /********************************************************************/
    /*				Comparators				*/
    /********************************************************************/

    // Eq
    
    template <>
    inline bool EvalHelper<char*, char*>::EvaluateEq()
    {
        return strcmp(e, v) == 0;
    }

    template <>
    inline bool EvalHelper<char*, const char*>::EvaluateEq()
    {
        return strcmp(e, v) == 0;
    }

    template <>
    inline bool EvalHelper<const char*, char*>::EvaluateEq()
    {
        return strcmp(e, v) == 0;
    }

    template <>
    inline bool EvalHelper<const char*, const char*>::EvaluateEq()
    {
        return strcmp(e, v) == 0;
    }

    // Neq

    template <>
    inline bool EvalHelper<char*, char*>::EvaluateNeq()
    {
        return strcmp(e, v) != 0;
    }

    template <>
    inline bool EvalHelper<char*, const char*>::EvaluateNeq()
    {
        return strcmp(e, v) != 0;
    }

    template <>
    inline bool EvalHelper<const char*, char*>::EvaluateNeq()
    {
        return strcmp(e, v) != 0;
    }

    template <>
    inline bool EvalHelper<const char*, const char*>::EvaluateNeq()
    {
        return strcmp(e, v) != 0;
    }
}  // namespace cspec
