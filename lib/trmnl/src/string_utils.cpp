#include <string_utils.h>
#include <cstdio>
#include <cstring>

void api_hostname(const char* url, char* out, size_t out_size) {
    if (out_size == 0) return;
    const char* p = url;
    const char* scheme = strstr(p, "://");
    if (scheme) p = scheme + 3;
    size_t n = strcspn(p, "/:");
    if (n >= out_size) n = out_size - 1;
    memcpy(out, p, n);
    out[n] = '\0';
}

void format_message_truncated(char* buffer, int max_size, const char* format, va_list args) {
    int actual_len = vsnprintf(buffer, max_size, format, args);
    if (actual_len >= max_size) {
        strcpy(buffer + max_size - 4, "...");
    }
}