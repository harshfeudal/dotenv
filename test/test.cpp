#include "test.h"

int main() {
    dotenv::load("./test/.env");

    // Original
    run_test("BASIC");
    run_test("AFTER_LINE");
    run_test("EMPTY");
    run_test("EMPTY_WITH_SPACE");
    run_test("EMPTY_SINGLE_QUOTES");
    run_test("EMPTY_DOUBLE_QUOTES");
    run_test("EMPTY_BACKTICKS");
    run_test("SINGLE_QUOTES");
    run_test("SINGLE_QUOTES_SPACED");
    run_test("DOUBLE_QUOTES");
    run_test("DOUBLE_QUOTES_SPACED");
    run_test("DOUBLE_QUOTES_INSIDE_SINGLE");
    run_test("DOUBLE_QUOTES_WITH_NO_SPACE_BRACKET");
    run_test("SINGLE_QUOTES_INSIDE_DOUBLE");
    run_test("BACKTICKS_INSIDE_SINGLE");
    run_test("BACKTICKS_INSIDE_DOUBLE");
    run_test("BACKTICKS");
    run_test("BACKTICKS_SPACED");
    run_test("DOUBLE_QUOTES_INSIDE_BACKTICKS");
    run_test("SINGLE_QUOTES_INSIDE_BACKTICKS");
    run_test("DOUBLE_AND_SINGLE_QUOTES_INSIDE_BACKTICKS");
    run_test("EXPAND_NEWLINES");
    run_test("DONT_EXPAND_UNQUOTED");
    run_test("DONT_EXPAND_SQUOTED");
    run_test("DONT_EXPAND_SQUOTED");
    run_test("INLINE_COMMENTS");
    run_test("INLINE_COMMENTS_SINGLE_QUOTES");
    run_test("INLINE_COMMENTS_DOUBLE_QUOTES");
    run_test("INLINE_COMMENTS_BACKTICKS");
    run_test("INLINE_COMMENTS_SPACE");
    run_test("EQUAL_SIGNS");
    run_test("RETAIN_INNER_QUOTES");
    run_test("RETAIN_INNER_QUOTES_AS_STRING");
    run_test("RETAIN_INNER_QUOTES_AS_BACKTICKS");
    run_test("TRIM_SPACE_FROM_UNQUOTED");
    run_test("USERNAME");
    run_test("SPACED_KEY");

    // Expansion
    run_test("BASIC_EXPAND");
    run_test("MACHINE");
    run_test("MACHINE_EXPAND");
    run_test("UNDEFINED_EXPAND");
    run_test("ESCAPED_EXPAND");
    run_test("DEFINED_EXPAND_WITH_DEFAULT");
    run_test("DEFINED_EXPAND_WITH_DEFAULT_NESTED");
    run_test("UNDEFINED_EXPAND_WITH_DEFINED_NESTED");
    run_test("UNDEFINED_EXPAND_WITH_DEFAULT");
    run_test("UNDEFINED_EXPAND_WITH_DEFAULT_NESTED");
    run_test("DEFINED_EXPAND_WITH_DEFAULT_NESTED_TWICE");
    run_test("UNDEFINED_EXPAND_WITH_DEFAULT_NESTED_TWICE");
    run_test("DEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS");
    run_test("UNDEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS");
    run_test("UNDEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS_NESTED");
    run_test("MONGOLAB_DATABASE");
    run_test("MONGOLAB_USER");
    run_test("MONGOLAB_PASSWORD");
    run_test("MONGOLAB_DOMAIN");
    run_test("MONGOLAB_PORT");
    run_test("MONGOLAB_URI");
    run_test("MONGOLAB_USER_RECURSIVELY");
    run_test("MONGOLAB_URI_RECURSIVELY");
    run_test("WITHOUT_CURLY_BRACES_URI");
    run_test("WITHOUT_CURLY_BRACES_USER_RECURSIVELY");
    run_test("WITHOUT_CURLY_BRACES_URI_RECURSIVELY");
    run_test("WITHOUT_CURLY_BRACES_UNDEFINED_EXPAND_WITH_DEFAULT_WITH_SPECIAL_CHARACTERS");

    return 0;
}