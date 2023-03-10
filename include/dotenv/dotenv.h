/*
 * Copyright 2023 harshfeudal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// MSVC warning disabled
#define _CRT_SECURE_NO_WARNINGS 1

#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

namespace dotenv {
    // Parse .env file contents into a map
    std::unordered_map<std::string, std::string> parse(const std::string& src) {
        std::unordered_map<std::string, std::string> map;
        std::regex line_regex(R"((?:^|\n)\s*(?:export\s+)?([\w.-]+)(?:\s*=\s*?|:\s+?)(\s*'(?:\\'|[^'])*'|\s*"(?:\\.|[^"\\])*"|\s*`(?:\\`|[^`])*`|[^#\r\n]+)?\s*(?:#.*)?(?:$|\n))");

        auto line_begin = std::sregex_iterator(src.begin(), src.end(), line_regex);
        auto line_end = std::sregex_iterator();
        for (std::sregex_iterator i = line_begin; i != line_end; ++i) {
            std::smatch match = *i;
            std::string key = match[1];
            std::string value = match[2];
            if (!value.empty()) {
                if (value[0] == '\'' || value[0] == '"' || value[0] == '`') {
                    value = value.substr(1, value.size() - 2);
                    // Handle escaped characters
                    size_t pos = 0;
                    while ((pos = value.find("\\", pos)) != std::string::npos) {
                        if (pos + 1 < value.size()) {
                            char c = value[pos + 1];
                            if (c == '"' || c == '\'' || c == '\\') {
                                value.erase(pos, 1);
                            }
                            else if (c == 'n') {
                                value.replace(pos, 2, "\n");
                            }
                            else if (c == 'r') {
                                value.replace(pos, 2, "\r");
                            }
                            else if (c == 't') {
                                value.replace(pos, 2, "\t");
                            }
                        }
                        ++pos;
                    }
                }
                map[key] = value;
            }
        }

        // Substitute environment variables
        for (auto& pair : map) {
            std::string value = pair.second;
            if (value.empty()) {
                // If the value is an empty string, unset the environment variable
                std::string key = pair.first;
                _putenv((key + "=").c_str());
            }
            else {
                size_t pos = 0;
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
                                std::string key = value.substr(pos + 2, end - pos - 2);
                                auto it = map.find(key);
                                if (it != map.end()) {
                                    value.replace(pos, end - pos + 1, it->second);
                                    pos += it->second.size();
                                }
                                else {
                                    pos = end + 1;
                                }
                            }
                            else {
                                pos += 2;
                            }
                        }
                        else {
                            // Substitution without curly braces
                            size_t end = pos + 1;
                            while (end < value.size() && std::isalnum(value[end])) {
                                ++end;
                            }
                            std::string key = value.substr(pos + 1, end - pos - 1);
                            auto it = map.find(key);
                            if (it != map.end()) {
                                value.replace(pos, end - pos, it->second);
                                pos += it->second.size();
                            }
                            else {
                                pos = end;
                            }
                        }
                    }
                    else {
                        ++pos;
                    }
                }
                pair.second = value;

                // Set the environment variable
                std::string key = pair.first;
                std::string env_string = key + "=" + pair.second;
                _putenv(env_string.c_str());
            }
        }

        return map;
    }

    // Load .env file and populate environment variables
    void load(const std::string & path) {
        std::ifstream file(path);
        if (file.is_open()) {
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            std::unordered_map<std::string, std::string> map = parse(contents);
            for (const auto& pair : map) {
                _putenv((pair.first + "=" + pair.second).c_str());
            }
        }
    }
}
