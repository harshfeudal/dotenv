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
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

namespace dotenv {
	// Parse .env file contents into a map
	std::unordered_map<std::string, std::string> parse(const std::string& src) {
		std::unordered_map<std::string, std::string> map;
		std::regex line_regex(R"((?:^|\n)\s*(?:export\s+)?([\w.-]+)(?:\s*=\s*?|:\s+?)(\s*'(?:\\'|[^'])*'|\s*"(?:\\"|[^"])*"|\s*`(?:\\`|[^`])*`|[^#\r\n]+)?\s*(?:#.*)?(?:$|\n))");

		auto line_begin = std::sregex_iterator(src.begin(), src.end(), line_regex);
		auto line_end = std::sregex_iterator();
		for (std::sregex_iterator i = line_begin; i != line_end; ++i) {
			std::smatch match = *i;
			std::string key = match[1];
			std::string value = match[2];
			if (!value.empty()) {
				if (value[0] == '\'' || value[0] == '"' || value[0] == '`') {
					value = value.substr(1, value.size() - 2);
				}
				map[key] = value;
			}
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
				_putenv((pair.first + "=" + pair.second).c_str());
			}
		}
	}
}
