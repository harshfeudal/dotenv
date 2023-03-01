#include <dotenv/dotenv.h>
#include <iostream>

int main()
{
	// Read file:
	// Navigate it if you're put it in a folder like me.
	Dotenv config("./test/.env");

	// Test what it logs:
	std::cout << "Hello: " << config.Get("HELLO") << std::endl;
	std::cout << "Read number: " << config.Get("READ_NUMBER") << std::endl;
	std::cout << "Read base64: " << config.Get("READ_BASE64") << std::endl;
	std::cout << "Read symbol: " << config.Get("READ_SYMBOL") << std::endl;
	std::cout << "Harshfeudal: " << config.Get("HARSHFEUDAL") << std::endl;

	return 0;
}