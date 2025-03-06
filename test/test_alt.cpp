/**
 * The MIT License (MIT)
 * Copyright (c) 2025 harshfeudal
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <dotenv/dotenv-alt.h>

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
    std::cout << "Testing [dotenv-alt.h] version: " << DOTENV_ALT_VERSION << std::endl;
    
    if (!dotenv::load(".env")) {
        std::cerr << "Failed to load .env file" << std::endl;
        return 1;
    }

    std::ofstream out_file("output_alt.txt");
    if (!out_file.is_open()) {
        std::cerr << "Failed to open output_alt.txt" << std::endl;
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
            std::string actual = dotenv::get(test_case.key);
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
        std::cout << red << "Failed Tests (Non-OOP):\n" << reset;
        for (const auto& failed : failed_tests) {
            std::cout << "  Key: " << failed.key << "\n";
            std::cout << "    Actual: \"" << failed.actual << "\"\n";
            std::cout << "    Expected: \"" << failed.expected << "\"\n";
        }
        std::cout << "\n";
    }

    std::cout << green << "Passed (dotenv-alt.h): [" << passed_tests << "/" << total_tests << "]" << reset << std::endl;

    out_file.close();
    return (passed_tests == total_tests) ? 0 : 1;
}
