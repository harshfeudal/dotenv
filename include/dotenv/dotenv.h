#ifndef DOTENV_H
#define DOTENV_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <cctype>
#include <cstring>

class Dotenv {
public:
    Dotenv() = default;

    bool load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return false;
        }

        file.sync_with_stdio(false);
        std::string line;
        line.reserve(256);
        while (std::getline(file, line)) {
            parse_line(line);
        }

        return true;
    }

    std::string get(const std::string& key, const std::string& default_value = "") const {
        auto it = env_map.find(key);
        return (it != env_map.end()) ? it->second : default_value;
    }

private:
    std::unordered_map<std::string, std::string> env_map;

    void parse_line(std::string& line) {
        line = remove_comments(line);
        trim_in_place(line);
        if (line.empty()) {
            return;
        }

        size_t equal_pos = line.find('=');
        if (equal_pos == std::string::npos) {
            return;
        }

        std::string key;
        key.reserve(equal_pos);
        key.assign(line.data(), equal_pos);
        trim_in_place(key);

        std::string value;
        value.reserve(line.size() - equal_pos - 1);
        value.assign(line.data() + equal_pos + 1, line.size() - equal_pos - 1);

        bool is_double_quoted = false;
        bool is_single_quoted = false;
        bool is_backtick_quoted = false;

        if (!value.empty()) {
            if (value.front() == '"' && value.back() == '"') {
                is_double_quoted = true;
                value = value.substr(1, value.length() - 2);
            }
            else if (value.front() == '\'' && value.back() == '\'') {
                is_single_quoted = true;
                value = value.substr(1, value.length() - 2);
            }
            else if (value.front() == '`' && value.back() == '`') {
                is_backtick_quoted = true;
                value = value.substr(1, value.length() - 2);
            }
            else {
                bool is_all_whitespace = true;
                for (char ch : value) {
                    if (!std::isspace(static_cast<unsigned char>(ch))) {
                        is_all_whitespace = false;
                        break;
                    }
                }
                if (!is_all_whitespace) {
                    trim_in_place(value);
                }
            }
        }
        else {
            value.clear();
        }

        if (is_double_quoted) {
            process_escapes_in_place(value);
        }

        if (!is_single_quoted && !is_double_quoted && !is_backtick_quoted) {
            expand_variables_in_place(value);
        }

        env_map.emplace(std::move(key), std::move(value));
    }

    std::string remove_comments(const std::string& line) {
        bool in_single_quotes = false;
        bool in_double_quotes = false;
        bool in_backticks = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char ch = line[i];
            if (ch == '\'' && !in_double_quotes && !in_backticks) {
                in_single_quotes = !in_single_quotes;
            }
            else if (ch == '"' && !in_single_quotes && !in_backticks) {
                in_double_quotes = !in_double_quotes;
            }
            else if (ch == '`' && !in_single_quotes && !in_double_quotes) {
                in_backticks = !in_backticks;
            }
            else if (ch == '#' && !in_single_quotes && !in_double_quotes && !in_backticks && (i == 0 || std::isspace(static_cast<unsigned char>(line[i - 1])))) {
                return line.substr(0, i);
            }
        }
        return line;
    }

    void process_escapes_in_place(std::string& str) {
        size_t write_pos = 0;
        for (size_t read_pos = 0; read_pos < str.length(); ++read_pos) {
            if (str[read_pos] == '\\' && read_pos + 1 < str.length()) {
                ++read_pos;
                char ch = str[read_pos];
                if (ch == 'n') str[write_pos++] = '\n';
                else if (ch == 't') str[write_pos++] = '\t';
                else if (ch == 'r') str[write_pos++] = '\r';
                else if (ch == '\\') str[write_pos++] = '\\';
                else str[write_pos++] = ch;
            }
            else {
                str[write_pos++] = str[read_pos];
            }
        }
        str.resize(write_pos);
    }

    void expand_variables_in_place(std::string& value) {
        size_t start_pos = 0;
        while ((start_pos = value.find('$', start_pos)) != std::string::npos) {
            if (start_pos > 0 && value[start_pos - 1] == '\\') {
                value.erase(start_pos - 1, 1);
                start_pos++;
                continue;
            }

            size_t end_pos = start_pos + 1;

            if (end_pos < value.length() && value[end_pos] == '{') {
                end_pos++;
                size_t var_start = end_pos;
                bool has_default = false;

                while (end_pos < value.length() && value[end_pos] != '}' && value[end_pos] != ':') {
                    end_pos++;
                }

                std::string var_name(value.data() + var_start, end_pos - var_start);
                std::string default_value;

                if (end_pos < value.length() && value[end_pos] == ':') {
                    end_pos++;
                    if (end_pos < value.length() && value[end_pos] == '-') {
                        has_default = true;
                        end_pos++;
                        size_t default_start = end_pos;
                        int brace_count = 0;

                        while (end_pos < value.length()) {
                            if (value[end_pos] == '{') brace_count++;
                            if (value[end_pos] == '}') {
                                if (brace_count == 0) break;
                                brace_count--;
                            }
                            end_pos++;
                        }

                        if (end_pos < value.length()) {
                            default_value.assign(value.data() + default_start, end_pos - default_start);
                        }
                    }
                }

                if (end_pos < value.length() && value[end_pos] == '}') {
                    std::string var_value = get(var_name);
                    if (var_value.empty() && has_default) {
                        var_value = default_value;
                        expand_variables_in_place(var_value);
                    }
                    value.replace(start_pos, end_pos - start_pos + 1, var_value);
                    start_pos += var_value.length();
                }
                else {
                    start_pos++;
                }
            }
            else {
                size_t var_end = end_pos;
                while (var_end < value.length() && (std::isalnum(static_cast<unsigned char>(value[var_end])) || value[var_end] == '_')) {
                    var_end++;
                }

                std::string var_name(value.data() + start_pos + 1, var_end - (start_pos + 1));
                std::string var_value;

                if (var_end < value.length() && value[var_end] == ':' && var_end + 1 < value.length() && value[var_end + 1] == '-') {
                    var_end += 2;
                    size_t default_start = var_end;
                    while (var_end < value.length() && value[var_end] != ' ' && value[var_end] != '\t' && value[var_end] != '\n' && value[var_end] != '\r') {
                        var_end++;
                    }
                    std::string default_value(value.data() + default_start, var_end - default_start);
                    var_value = get(var_name);
                    if (var_value.empty()) {
                        var_value = default_value;
                        expand_variables_in_place(var_value);
                    }
                    value.replace(start_pos, var_end - start_pos, var_value);
                    start_pos += var_value.length();
                }
                else {
                    var_value = get(var_name);
                    value.replace(start_pos, var_end - start_pos, var_value);
                    start_pos += var_value.length();
                }
            }
        }
    }

    void trim_in_place(std::string& str) {
        size_t start = 0;
        size_t end = str.length();

        while (start < str.length() && std::isspace(static_cast<unsigned char>(str[start]))) {
            start++;
        }
        while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
            end--;
        }

        if (start >= end) {
            str.clear();
        }
        else if (start > 0 || end < str.length()) {
            str.assign(str.data() + start, end - start);
        }
    }
};

#endif // DOTENV_H
