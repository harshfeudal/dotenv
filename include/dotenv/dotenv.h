#pragma once

// MSVC warning disabled
#define _CRT_SECURE_NO_WARNINGS 1

#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>
#include <iostream>
#include <unordered_map>

namespace dotenv {
    // Parse .env file contents into a map
    std::unordered_map<std::string, std::string> parse(const std::string& src) {
        std::unordered_map<std::string, std::string> map;
        std::regex line_regex(R"((?:^|\n)\s*(?:export\s+)?([\w.-]+)(?:\s*=\s*?|:\s+?)(\s*'(?:\\[abfnrtv\\'\?]|[^'\\])*'|\s*"(?:\\[abfnrtv\\"\\?]|[^"\\])*"|\s*`(?:\\[abfnrtv\\`\\]|[^`])*`|[^#\r\n]+)?\s*(?:#.*)?(?:$|\n))");

        auto line_begin = std::sregex_iterator(src.begin(), src.end(), line_regex);
        auto line_end   = std::sregex_iterator();
        
        for (std::sregex_iterator i = line_begin; i != line_end; ++i) {

            std::smatch match = *i;
            std::string key   = match[1];
            std::string value = match[2];

            if (!value.empty()) {
                if (value[0] == '\'' || value[0] == '"' || value[0] == '`') {
                    value = value.substr(1, value.size() - 2);
                    // Handle escaped characters
                    size_t pos = 0;
                    while ((pos = value.find("\\", pos)) != std::string::npos) {
                        if (pos + 1 < value.size()) {
                            char c = value[pos + 1];
                            if (c == '"' || c == '\'' || c == '\\' || c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '?' || c == '\'') {
                                if (c == 'a') { value.replace(pos, 2, "\a"); }
                                else if (c == 'b')  { value.replace(pos, 2, "\b"); }
                                else if (c == 'f')  { value.replace(pos, 2, "\f"); }
                                else if (c == 'n')  { value.replace(pos, 2, "\n"); }
                                else if (c == 'r')  { value.replace(pos, 2, "\r"); }
                                else if (c == 't')  { value.replace(pos, 2, "\t"); }
                                else if (c == 'v')  { value.replace(pos, 2, "\v"); }
                                else if (c == '\'') { value.replace(pos, 2, "\'"); }
                                else if (c == '\"') { value.replace(pos, 2, "\""); }
                                else if (c == '\\') { value.replace(pos, 2, "\\"); }
                                else if (c == '\?') { value.replace(pos, 2, "\?"); }
                            }
                        }
                        ++pos;
                    }
                }

                map[key] = value;
            }
            else {
                // If the value is an empty string, set the variable in the environment with an
                // empty string value
                _putenv((key + "=").c_str());
            }
        }

        // Substitute environment variables
        for (auto& pair : map) {

            std::string value = pair.second;
            size_t      pos   = 0;

            while ((pos = value.find("$", pos)) != std::string::npos) {
                if (pos + 1 < value.size()) {

                    if (value[pos + 1] == '$') {
                        // Handle escaped $
                        value.erase(pos, 1);
                        ++pos;
                    }
                    else if (value[pos + 1] == '{') {
                        // Substitution with curly braces
                        size_t end = value.find("}", pos + 2);

                        if (end != std::string::npos) {

                            std::string key_with_default = value.substr(pos + 2, end - pos - 2);
                            size_t colon_pos = key_with_default.find(":");
                            std::string key, default_value;

                            if (colon_pos == std::string::npos) {
                                // No default value provided
                                key = key_with_default;

                                if (map.find(key) != map.end()) {
                                    // Key found in map, substitute with value
                                    value.replace(pos, end - pos + 1, map[key]);
                                    pos += map[key].size();
                                }
                                else {
                                    // Key not found in map, remove substitution
                                    value.erase(pos, end - pos + 1);
                                }
                            }
                            else {
                                // Default value provided
                                key = key_with_default.substr(0, colon_pos);
                                std::string default_value = key_with_default.substr(colon_pos + 1);

                                if (map.find(key) != map.end()) {
                                    // Key found in map, substitute with value
                                    value.replace(pos, end - pos + 1, map[key]);
                                    pos += map[key].size();
                                }
                                else {
                                    // Key not found in map, substitute with default value
                                    value.replace(pos, end - pos + 1, default_value);
                                    pos += default_value.size();
                                }
                            }
                        }
                        else {
                            // No matching } found, remove substitution
                            value.erase(pos, 2);
                        }
                    }
                    else {
                        // Substitution without curly braces
                        std::string key = value.substr(pos + 1, 1);
                        if (map.find(key) != map.end()) {
                            // Key found in map, substitute with value
                            value.replace(pos, 2, map[key]);
                            pos += map[key].size();
                        }
                        else {
                            // Key not found in map, remove substitution
                            value.erase(pos, 2);
                        }
                    }
                }
                else {
                    // $ is at end of string, remove substitution
                    value.erase(pos, 1);
                }
            }

            pair.second = value;
        }

        return map;
    }

    // Load .env file and populate environment variables
    void load(const std::string& path) {
        std::ifstream file(path);
        if (file.is_open()) {

            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            std::unordered_map<std::string, std::string> map = parse(contents);

            for (const auto& pair : map) {

                std::string key   = pair.first;
                std::string value = pair.second;

                if (value.empty()) {
                    // If the value is an empty string, set it to the default value if available
                    size_t colon_pos = key.find(":");
                    std::string env_key, default_value;

                    if (colon_pos != std::string::npos) {
                        env_key = key.substr(0, colon_pos);
                        default_value = key.substr(colon_pos + 1);
                    }
                    else {
                        env_key = key;
                    }
                    if (!default_value.empty()) {
                        value = default_value;
                    }
                }

                _putenv((key + "=" + value).c_str());
            }
        }
    }
}
