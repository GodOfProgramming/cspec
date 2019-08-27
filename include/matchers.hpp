#pragma once

namespace cspec {
  namespace matchers {
    template <typename E, typename V>
    class Matcher {
     public:
      virtual ~Matcher() {
      }

      bool operator()(V value) {
        throw std::runtime_error("Invalid Matcher");
      };

     protected:
      Matcher(const E& expectation) : mExpectation(expectation) {
      }

      const E& mExpectation;
    };

    template <typename E, typename V>
    class ToEqual : public Matcher<E, V> {
     public:
      ToEqual(E expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(const V& value) {
        return mExpectation == value;
      }
    };

    template <typename E, typename V>
    class NotToEqual : public Matcher<E, V> {
     public:
      NotToEqual(E expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) {
        return mExpectation != value;
      }
    };

    template <typename E, typename V>
    class ToContain : public Matcher<E, V> {
     public:
      ToContain(E expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) {
        for (auto& element : mExpectation) {
          if (element == value) {
            return true;
          }
        }
        return false;
      }
    };

    template <typename E, typename V>
    class NotToContain : public Matcher<E, V> {
     public:
      NotToContain(E expectation) : Matcher<E, V>(expectation) {
      }

      bool operator()(V value) {
        for (auto& element : mExpectation) {
          if (element == value) {
            return false;
          }
        }

        return true;
      }
    };
  }  // namespace matchers
}  // namespace cspec

