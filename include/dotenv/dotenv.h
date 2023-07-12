#ifndef DOTENV_H
#define DOTENV_H

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

class Dotenv 
{
public:
    void config(std::string filename = ".env") 
    {
        std::ifstream file(filename);

        if (!file.is_open())
            throw std::runtime_error("Failed to open .env file");

        std::string line;
        while (std::getline(file, line)) 
        {
            if (isComment(line))
                continue;

            expandVariables(line);
            parseLine(line);
        }

        file.close();
    }

    bool has(const std::string& key) const 
    {
        return env_data.find(key) != env_data.end();
    }

    std::string get(const std::string& key) const 
    {
        if (!has(key))
            throw std::runtime_error("Undefined key: " + key);

        return env_data.at(key);
    }

private:
    std::unordered_map<std::string, std::string> env_data;

    bool isComment(const std::string& line) 
    {
        return line.find("#") == 0;
    }

    void expandVariables(std::string& line) 
    {
        std::size_t pos = 0;
        while ((pos = line.find('$', pos)) != std::string::npos) 
        {
            if (pos + 1 < line.length()) 
            {
                if (line[pos + 1] == '\\') 
                {
                    line.erase(pos, 1);
                    ++pos;
                } 
                else if (line[pos + 1] == '{') 
                {
                    std::size_t endPos = line.find('}', pos + 2);

                    if (endPos != std::string::npos) 
                    {
                        std::string varName = line.substr(pos + 2, endPos - pos - 2);
                        std::string varValue = (has(varName)) ? get(varName) : "";
                        line.replace(pos, endPos - pos + 1, varValue);
                        pos += varValue.length();
                    } 
                    else
                        ++pos;
                } 
                else 
                {
                    std::string varName = line.substr(pos + 1);
                    std::string varValue = (has(varName)) ? get(varName) : "";
                    line.replace(pos, varName.length() + 1, varValue);
                    pos += varValue.length();
                }
            } else
                break;
        }
    }

    void parseLine(const std::string& line) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss >> std::ws, key, '=') && std::getline(iss >> std::ws, value)) 
            env_data[key] = value;
    }
};

#endif // DOTENV_H