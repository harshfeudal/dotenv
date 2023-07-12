#include <dotenv/dotenv.h>
#include <iostream>

int main()
{
    try 
    {
        Dotenv dotenv;
        dotenv.config();

        std::string STRING = dotenv.get("STRING");
        std::string STRING_QUOTE = dotenv.get("STRING_QUOTE");

        std::cout << "STRING = " << STRING << std::endl;
        std::cout << "STRING_QUOTE = " << STRING_QUOTE << std::endl;
    } 
    catch (const std::runtime_error& error) 
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    return 0;
}