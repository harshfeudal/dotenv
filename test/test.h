#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>
#include <utility>

struct test_case {
    std::string key;
    std::string expected;
};

struct test_category {
    std::string name;
    std::vector<test_case> cases;
};

inline std::vector<test_category> get_test_categories() {
    return {
        {"Basic Key-Value Pairs", {
            {"BASIC", "basic"},
            {"AFTER_LINE", "after_line"}
        }},
        {"Empty Values", {
            {"EMPTY", ""},
            {"EMPTY_WITH_SPACE", ""},
            {"EMPTY_SINGLE_QUOTES", ""},
            {"EMPTY_DOUBLE_QUOTES", ""},
            {"EMPTY_BACKTICKS", ""}
        }},
        {"Quoted Values", {
            {"SINGLE_QUOTES", "single_quotes"},
            {"SINGLE_QUOTES_SPACED", "    single quotes    "},
            {"DOUBLE_QUOTES", "double_quotes"},
            {"DOUBLE_QUOTES_SPACED", "    double quotes    "},
            {"DOUBLE_QUOTES_INSIDE_SINGLE", "double \"quotes\" work inside single quotes"},
            {"DOUBLE_QUOTES_WITH_NO_SPACE_BRACKET", "{ port: $MONGOLAB_PORT}"},
            {"SINGLE_QUOTES_INSIDE_DOUBLE", "single 'quotes' work inside double quotes"},
            {"BACKTICKS_INSIDE_SINGLE", "`backticks` work inside single quotes"},
            {"BACKTICKS_INSIDE_DOUBLE", "`backticks` work inside double quotes"},
            {"BACKTICKS", "backticks"},
            {"BACKTICKS_SPACED", "    backticks    "},
            {"DOUBLE_QUOTES_INSIDE_BACKTICKS", "double \"quotes\" work inside backticks"},
            {"SINGLE_QUOTES_INSIDE_BACKTICKS", "single 'quotes' work inside backticks"},
            {"DOUBLE_AND_SINGLE_QUOTES_INSIDE_BACKTICKS", "double \"quotes\" and single 'quotes' work inside backticks"}
        }},
        {"Newline Handling", {
            {"EXPAND_NEWLINES", "expand\nnew\nlines"},
            {"DONT_EXPAND_UNQUOTED", "dontexpand\\nnewlines"},
            {"DONT_EXPAND_SQUOTED", "dontexpand\\nnewlines"}
        }},
        {"Comments", {
            {"INLINE_COMMENTS", "inline comments"},
            {"INLINE_COMMENTS_SINGLE_QUOTES", "inline comments outside of #singlequotes"},
            {"INLINE_COMMENTS_DOUBLE_QUOTES", "inline comments outside of #doublequotes"},
            {"INLINE_COMMENTS_BACKTICKS", "inline comments outside of #backticks"},
            {"INLINE_COMMENTS_SPACE", "inline comments start with a#number sign. no space required."}
        }},
        {"Special Characters and Trimming", {
            {"EQUAL_SIGNS", "equals=="},
            {"RETAIN_INNER_QUOTES", "{\"foo\": \"bar\"}"},
            {"RETAIN_INNER_QUOTES_AS_STRING", "{\"foo\": \"bar\"}"},
            {"RETAIN_INNER_QUOTES_AS_BACKTICKS", "{\"foo\": \"bar's\"}"},
            {"TRIM_SPACE_FROM_UNQUOTED", "some spaced out string"},
            {"USERNAME", "therealnerdybeast@example.tld"},
            {"SPACED_KEY", "parsed"}
        }},
        {"Variable Expansion", {
            {"BASIC_EXPAND", "basic"},
            {"MACHINE", "machine_env"},
            {"MACHINE_EXPAND", "machine_env"},
            {"UNDEFINED_EXPAND", ""},
            {"ESCAPED_EXPAND", "$ESCAPED"},
            {"DEFINED_EXPAND_WITH_DEFAULT", "machine_env"},
            {"DEFINED_EXPAND_WITH_DEFAULT_NESTED", "machine_env"},
            {"UNDEFINED_EXPAND_WITH_DEFINED_NESTED", "machine_env"},
            {"UNDEFINED_EXPAND_WITH_DEFAULT", "default"},
            {"UNDEFINED_EXPAND_WITH_DEFAULT_NESTED", "default"},
            {"DEFINED_EXPAND_WITH_DEFAULT_NESTED_TWICE", "machine_envdefault"},
            {"UNDEFINED_EXPAND_WITH_DEFAULT_NESTED_TWICE", "default"},
            {"DEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS", "machine_env"},
            {"UNDEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS", "/default/path:with/colon"},
            {"UNDEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS_NESTED", "/default/path:with/colon"}
        }},
        {"Complex URI Expansion", {
            {"MONGOLAB_DATABASE", "heroku_db"},
            {"MONGOLAB_USER", "username"},
            {"MONGOLAB_PASSWORD", "password"},
            {"MONGOLAB_DOMAIN", "abcd1234.mongolab.com"},
            {"MONGOLAB_PORT", "12345"},
            {"MONGOLAB_URI", "mongodb://username:password@abcd1234.mongolab.com:12345/heroku_db"},
            {"MONGOLAB_USER_RECURSIVELY", "username:password"},
            {"MONGOLAB_URI_RECURSIVELY", "mongodb://username:password@abcd1234.mongolab.com:12345/heroku_db"},
            {"WITHOUT_CURLY_BRACES_URI", "mongodb://username:password@abcd1234.mongolab.com:12345/heroku_db"},
            {"WITHOUT_CURLY_BRACES_USER_RECURSIVELY", "username:password"},
            {"WITHOUT_CURLY_BRACES_URI_RECURSIVELY", "mongodb://username:password@abcd1234.mongolab.com:12345/heroku_db"},
            {"WITHOUT_CURLY_BRACES_UNDEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS", "/default/path:with/colon"}
        }}
    };
}

#endif // TEST_H
