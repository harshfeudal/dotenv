#include <dotenv/dotenv.h>

#include <iostream>
#include <chrono>

#include "test.h"

int main() {
	dotenv::load("./test/.env");

    std::cout << "Bool test: " << std::endl;
    {
        Timer timer;
        const char* my_var = std::getenv("MY_BOOL");
        if (my_var) {
            std::cout << "MY_RESULT=" << my_var << std::endl;
        }
        else {
            std::cerr << "MY_RESULT not found in environment" << std::endl;
        }
    }
    std::cout << std::endl;

	std::cout << "Int test: " << std::endl;
	{
		Timer timer;
		const char* my_var = std::getenv("MY_INT");
		if (my_var) {
			std::cout << "MY_RESULT=" << my_var << std::endl;
		}
		else {
			std::cerr << "MY_RESULT not found in environment" << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Long test: " << std::endl;
	{
		Timer timer;
		const char* my_var = std::getenv("MY_LONG");
		if (my_var) {
			std::cout << "MY_RESULT=" << my_var << std::endl;
		}
		else {
			std::cerr << "MY_RESULT not found in environment" << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "String test: " << std::endl;
	{
		Timer timer;
		const char* my_var = std::getenv("MY_STRING");
		if (my_var) {
			std::cout << "MY_RESULT=" << my_var << std::endl;
		}
		else {
			std::cerr << "MY_RESULT not found in environment" << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Harshfeudal test: " << std::endl;
	{
		Timer timer;
		const char* my_var = std::getenv("MY_HARSHFEUDAL");
		if (my_var) {
			std::cout << "MY_RESULT=" << my_var << std::endl;
		}
		else {
			std::cerr << "MY_RESULT not found in environment" << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Hash test: " << std::endl;
	{
		Timer timer;
		const char* my_var = std::getenv("MY_HASH");
		if (my_var) {
			std::cout << "MY_RESULT=" << my_var << std::endl;
		}
		else {
			std::cerr << "MY_RESULT not found in environment" << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Spacing test: " << std::endl;
	{
		Timer timer;
		const char* my_var = std::getenv("MY_SPACING");
		if (my_var) {
			std::cout << "MY_RESULT=" << my_var << std::endl;
		}
		else {
			std::cerr << "MY_RESULT not found in environment" << std::endl;
		}
	}
	std::cout << std::endl;

    std::cout << "Complex test: " << std::endl;
    {
        Timer timer;
        const char* my_var = std::getenv("MY_COMPLEX");
        if (my_var) {
            std::cout << "MY_RESULT=" << my_var << std::endl;
        }
        else {
            std::cerr << "MY_RESULT not found in environment" << std::endl;
        }
    }
    std::cout << std::endl;

	return 0;
}