#include "cspec/cspec.hpp"

#include <algorithm>

extern char** environ;
std::unordered_map<std::string, std::string> ENV;
std::vector<std::string> ARGV;

void init_env();
void init_argv(int argc, char* argv[]);
bool check_opt(const char* opt);

int main(int argc, char* argv[])
{
    init_env();
    init_argv(argc, argv);

    // if --no-eval is not present
    if (!check_opt("--no-eval")) {
        cspec::Evaluation::Run();

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
    }

    if (check_opt("--bench")) {
        cspec::Benchmark::Run();
    }

    return !cspec::gFailures ? 0 : 1;
}

void init_env()
{
    for (int i = 0; environ[i]; i++) {
        std::string env = environ[i];

        auto eqpos = env.find_first_of('=');
        auto k = env.substr(0, eqpos);
        auto v = env.substr(eqpos + 1);

        ENV[k] = v;
    }
}

void init_argv(int argc, char* argv[])
{
    ARGV.resize(argc);
    for (int i = 0; i < argc; i++) {
        ARGV[i] = std::string(argv[i]);
    }
}

bool check_opt(const char* opt)
{
    return std::find(ARGV.begin(), ARGV.end(), std::string(opt)) != ARGV.end();
}

