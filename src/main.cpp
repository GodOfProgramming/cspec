#include <algorithm>
#include "cspec.hpp"
#include "benchmark.hpp"

extern char** environ;
std::unordered_map<std::string, std::string> ENV;
std::vector<const char*> ARGV;

int main(int argc, char* argv[])
{
    for (int i = 0; environ[i]; i++) {
        std::string env = environ[i];

        auto eqpos = env.find_first_of('=');
        auto k = env.substr(0, eqpos);
        auto v = env.substr(eqpos + 1);

        ENV[k] = v;
    }

    ARGV.resize(argc);
    for (int i = 0; i < argc; i++) {
        ARGV[i] = argv[i];
    }

    std::sort(cspec::gTests.begin(), cspec::gTests.end(), [](cspec::CspecTest* a, cspec::CspecTest* b) -> bool {
        return strcmp(a->TestName, b->TestName) < 0;
    });

    cspec::print("Running ", cspec::gTests.size(), " evaluations\n");
    for (auto& test : cspec::gTests) {
        cspec::print('\n', "Evaluating: ", "\x1b[35m", test->TestName, '\n');
        test->body();
    }

    cspec::print('\n', cspec::captures());

    cspec::print("\n\n",
        "Evaluated ",
        cspec::gSpecCount,
        " test",
        cspec::gSpecCount == 1 ? "" : "s",
        " with ",
        cspec::gFailures,
        " failure",
        cspec::gFailures == 1 ? "" : "s",
        '\n');
    return !cspec::gFailures ? 0 : 1;
}
