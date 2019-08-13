#pragma once
#include <vector>

/* Vector that behaves like a stack but can be iterated */
template <typename T>
class CustomVector {
  public:
    void push(T val) {
      if (mInternal.size() < mInternalPtr) {
	mInternal.resize(mInternal.size() * 1.4);
      }

      mInternal[mInternalPtr++] = val;
    }

    T pop() {
      return mInternal[mInternalPtr >= 0 ? mInternalPtr-- : 0];
    }

    auto begin() {
      return mInternal.begin();
    }

    auto end() {
      return mInternal.end();
    }

    void clear() {
      mInternal.resize(0);
    };

  private:
    std::vector<T> mInternal;
    size_t mInternalPtr = 0;
};
