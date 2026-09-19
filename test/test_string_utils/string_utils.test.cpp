#include <unity.h>
#include <string_utils.h>
#include <cstring>
#include <cstdarg>
#include <cstdio>

// Helper to test format_message_truncated with variadic args
void test_format_helper(char* buffer, int max_size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    format_message_truncated(buffer, max_size, format, args);
    va_end(args);
}

void test_format_message_no_truncation(void) {
    char buffer[100];
    
    test_format_helper(buffer, sizeof(buffer), "Hello %s", "World");
    
    TEST_ASSERT_EQUAL_STRING("Hello World", buffer);
}

void test_format_message_with_truncation(void) {
    char buffer[10];
    
    test_format_helper(buffer, sizeof(buffer), "This is a very long message");
    
    TEST_ASSERT_EQUAL_STRING("This i...", buffer);
}

void test_format_message_exact_fit(void) {
    char buffer[12];
    
    test_format_helper(buffer, sizeof(buffer), "Hello World");
    
    TEST_ASSERT_EQUAL_STRING("Hello World", buffer);
}

void test_format_message_truncation_boundary(void) {
    char buffer[8];
    
    test_format_helper(buffer, sizeof(buffer), "1234567890");
    
    TEST_ASSERT_EQUAL_STRING("1234...", buffer);
}

void test_api_hostname_strips_scheme_and_path(void) {
    char out[64];
    api_hostname("https://ertale.com/tarik", out, sizeof(out));
    TEST_ASSERT_EQUAL_STRING("ertale.com", out);
}

void test_api_hostname_bare_host(void) {
    char out[64];
    api_hostname("https://trmnl.app", out, sizeof(out));
    TEST_ASSERT_EQUAL_STRING("trmnl.app", out);
}

void test_api_hostname_drops_port_and_fits_buffer(void) {
    char out[8];
    api_hostname("http://example.org:8080/api", out, sizeof(out));
    TEST_ASSERT_EQUAL_STRING("example", out);
}

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void process() {
    UNITY_BEGIN();
    RUN_TEST(test_format_message_no_truncation);
    RUN_TEST(test_format_message_with_truncation);
    RUN_TEST(test_format_message_exact_fit);
    RUN_TEST(test_format_message_truncation_boundary);
    RUN_TEST(test_api_hostname_strips_scheme_and_path);
    RUN_TEST(test_api_hostname_bare_host);
    RUN_TEST(test_api_hostname_drops_port_and_fits_buffer);
    UNITY_END();
}

int main(int argc, char **argv) {
    process();
    return 0;
}