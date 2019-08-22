#pragma once
#include <vector>
#include <iostream>

namespace cspec {
  /* Vector that behaves like a stack but can be iterated */
  template <typename T>
  class CustomVector {
    public:
      void push(T val) {
	if (mInternalPtr < mInternal.size()) {
	  mInternal[mInternalPtr] = val;
	} else {
	  mInternal.push_back(val);
	}
	mInternalPtr++;
      }

      T pop() {
	return mInternal[mInternalPtr >= 0 ? mInternalPtr-- : 0];
      }

      auto begin() {
	return mInternal.begin();
      }

      auto end() {
	return mInternal.begin() + (mInternalPtr >= 0 ? mInternalPtr : 0);
      }

      void clear() {
	mInternal.resize(0);
      };

      const std::vector<T>& getInternal() const {
	return mInternal;
      }

      CustomVector<T>& operator=(const CustomVector& other) {
	this->mInternal = other.mInternal;
	this-> mInternalPtr = other.mInternalPtr;
	return *this;
      }

    private:
      std::vector<T> mInternal;
      size_t mInternalPtr = 0;
  };
}

