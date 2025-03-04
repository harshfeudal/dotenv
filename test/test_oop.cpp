#include <dotenv/dotenv.h>

#include "test.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define green "\033[32m"
#define red "\033[31m"
#define reset "\033[0m"

struct failed_test {
    std::string key;
    std::string actual;
    std::string expected;
};

void pass(const std::string& actual, const std::string& expected, bool& passed) {
    passed = (actual == expected);
}

int main() {
    Dotenv env;
    if (!env.load(".env")) {
        std::cerr << "Failed to load .env file" << std::endl;
        return 1;
    }

    std::ofstream out_file("output_oop.txt");
    if (!out_file.is_open()) {
        std::cerr << "Failed to open output_oop.txt" << std::endl;
        return 1;
    }

    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(out_file.rdbuf());

    auto categories = get_test_categories();
    int total_tests = 0;
    int passed_tests = 0;
    std::vector<failed_test> failed_tests;

    for (const auto& category : categories) {
        std::cout << category.name << ":\n";
        for (const auto& test_case : category.cases) {
            std::string actual = env.get(test_case.key);
            bool passed = false;
            pass(actual, test_case.expected, passed);
            if (passed) {
                passed_tests++;
            } else {
                failed_tests.push_back({test_case.key, actual, test_case.expected});
            }
            total_tests++;
            std::cout << "  " << test_case.key << ": " << actual << "\n";
        }
        std::cout << "\n";
    }

    std::cout.rdbuf(cout_buf);

    if (!failed_tests.empty()) {
        std::cout << red << "Failed Tests (OOP):\n" << reset;
        for (const auto& failed : failed_tests) {
            std::cout << "  Key: " << failed.key << "\n";
            std::cout << "    Actual: \"" << failed.actual << "\"\n";
            std::cout << "    Expected: \"" << failed.expected << "\"\n";
        }
        std::cout << "\n";
    }

    std::cout << green << "Passed (OOP): [" << passed_tests << "/" << total_tests << "]" << reset << std::endl;

    out_file.close();
    return (passed_tests == total_tests) ? 0 : 1;
}
