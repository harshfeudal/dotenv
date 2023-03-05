#include <dotenv/dotenv.h>
#include <iostream>

int main() {
	dotenv::load("./test/.env");
	const char* my_var = std::getenv("MY_LONG");
	if (my_var) {
		std::cout << "MY_RESULT=" << my_var << std::endl;
	}
	else {
		std::cerr << "MY_RESULT not found in environment" << std::endl;
	}
	return 0;
}