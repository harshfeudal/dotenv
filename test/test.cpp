#include <dotenv/dotenv.h>
#include <chrono>
#include "test.h"

void run_test(const std::string& name) {
    std::cout << name << " test: " << std::endl;
    {
        Timer timer;
        const char* my_var = std::getenv(("MY_" + name).c_str());
        if (my_var) {
            std::cout << "MY_RESULT=" << my_var << std::endl;
        }
        else {
            std::cerr << "MY_RESULT not found in environment" << std::endl;
        }
    }
    std::cout << std::endl;
}

int main() {
    dotenv::load("./test/.env");

    run_test("BOOL");
    run_test("INT");
    run_test("LONG");
    run_test("STRING");
    run_test("HARSHFEUDAL");
    run_test("HASH");
    run_test("SPACING");
    run_test("COMPLEX");
    run_test("EMPTY_STRING");

    return 0;
}
