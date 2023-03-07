#include <dotenv/dotenv.h>

#include <iostream>
#include <chrono>

class Timer
{
public:
	Timer() { m_StartTimepoint = std::chrono::high_resolution_clock::now(); }
	~Timer() { Stop(); }

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end   = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto   duration = end - start;
		double ms       = duration * 0.001;

		std::cout << duration << "us (" << ms << "ms)\n";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

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

	return 0;
}