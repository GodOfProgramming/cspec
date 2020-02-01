#pragma once
#include <cstring>
#include <string>
#include <sstream>

namespace
{
    template <typename... Args>
    inline FmtHelper(Args&&... args)
    {
        std::stringstream ss;
        ((ss << std::forward<Args>(args)), ...);
        return ss.str();
    }
}  // namespace

namespace cspec
{
    enum class MatchType
    {
        ToEqual,
        NotToEqual,
        ToContain,
        NotToContain
    };

    template <typename V, MatchType T>
    std::string FailureMessage(V& val);

    template <typename E, typename V, MatchType T>
    std::string FailureMessage(E& expect, V& val);

    template <typename E, typename V>
    inline std::string FailureMessage<MatchType::ToEqual>(E& expect, V& val)
    {
        return FmtHelper("Expected ", expect, " to equal ", val, '\n');
    }

    template <typename E, typename V>
    inline std::string FailureMessage<MatchType::NotToEqual>(E& expect, V& val)
    {
        return FmtHelper("Expected ", expect, " not to equal ", val, '\n');
    }

    template <typename V>
    inline std::string FailureMessage<MatchType::ToContain>(V& val)
    {
        return FmtHelper("Expected a container to contain ", val, '\n');
    }

    template <typename V>
    inline std::string FailureMessage<MatchType::NotToContain>(V& val)
    {
        return FmtHelper("Expected a container not to contain ", val, '\n');
    }

    template <typename E, typename V>
    class Matcher
    {
       public:
        Matcher(E& expect, V& val) : mExp(expect), mVal(val)
        {}

        template <MatchType T>
        bool matches();

       private:
        E& mExp;
        V& mVal;
    };

    template <typename E, typename V>
    inline bool Matcher<E, V>::matches<MatchType::ToEqual>()
    {
        return mExp == mVal;
    }

    template <typename E, typename V>
    inline bool Matcher<E, V>::matches<MatchType::NotToEqual>()
    {
        return mExp != mVal;
    }

    template <typename E, typename V>
    inline bool Matcher<E, V>::matches<MatchType::ToContain>()
    {
        for (auto& el : mExp) {
            if (el == mVal) {
                return true;
            }
        }
        return false;
    }

    template <typename E, typename V>
    inline bool Matcher<E, V>::matches<MatchType::NotToContain>()
    {
        for (auto& el : mExp) {
            if (el == mVal) {
                return false;
            }
        }
        return true;
    }

    /********************************************************************/
    /*			Specializations Below				*/
    /********************************************************************/

    template <>
    inline std::string FailureMessage<MatchType::ToEqual>(std::string& a, std::string& b)
    {
        return FmtHelper("Expected '", a, "' to equal '", b, '\n');
    }

    template <>
    inline std::string FailureMessage<MatchType::ToEqual>(std::string& a, const char*& b)
    {
        return FmtHelper("Expected '", a, "' to equal '", b, '\n');
    }

    template <>
    inline std::string FailureMessage<MatchType::ToEqual>(const char*& a, std::string& b)
    {
        return FmtHelper("Expected '", a, "' to equal '", b, '\n');
    }

    template <>
    inline std::string FailureMessage<MatchType::NotToEqual>(const char*& a, const char*& b)
    {
        return FmtHelper("Expected '", a, "' not to equal '", b, '\n');
    }

    template <>
    inline std::string FailureMessage<MatchType::ToEqual>(std::string& a, const char*& b)
    {
        return FmtHelper("Expected '", a, "' not to equal '", b, '\n');
    }

    template <>
    inline std::string FailureMessage<MatchType::ToEqual>(const char*& a, std::string& b)
    {
        return FmtHelper("Expected '", a, "' not to equal '", b, '\n');
    }

    template <>
    inline bool Matcher<const char*, const char*>::matches<MatchType::ToEqual>()
    {
        return strcmp(mExp, mVal) == 0;
    }

    template <>
    inline bool Matcher<const char*, const char*>::matches<MatchType::NotToEqual>()
    {
        return strcmp(mExp, mVal) != 0;
    }
}  // namespace cspec
