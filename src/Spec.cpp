#include "Spec.hpp"
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

static CustomVector<const char*> gTestDescStack;

std::queue<std::function<void(void)>> Spec::mTests;

bool gInItBlock = false;
static bool gAllPassed = true;

void RunFunc(std::function<void(void)> func) {
  try {
    func();
  } catch (InvalidExpectationException e) {
    std::cout << "Expectations can only be executed within it blocks" << std::endl;
    gAllPassed = false;
  }
}

void Describe(const char* desc, std::function<void(void)> func) {
  gTestDescStack.clear();
  gTestDescStack.push(desc);

  try {
    RunFunc(func);
  } catch (SpecFailureException e) {
    gAllPassed = false;
    int tabcount = 1;
    for (const auto& desc : gTestDescStack) {
      for (int i = 0; i < tabcount; i++) {
        std::cout << '\t';
      }
      std::cout << desc << std::endl;
    }
  }
}

void Context(const char* context, std::function<void(void)> func) {
  gTestDescStack.push(context);
  RunFunc(func);
}

void It(const char* test, std::function<void(void)> func) {
  gInItBlock = true;
  gTestDescStack.push(test);
  RunFunc(func); // don't need this wrapper, but for consistency
  gInItBlock = false;
}

void Spec::RunTests() {
  while(!mTests.empty()) {
    auto test = mTests.front();
    test();
    mTests.pop();
  }
}

int main(int argc, char* argv[]) {
  Spec::RunTests();
  return gAllPassed ? 0 : 1;
}
