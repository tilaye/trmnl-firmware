#pragma once

#include <cstdarg>
#include <cstddef>

void format_message_truncated(char* buffer, int max_size, const char* format, va_list args);

// The host part of an API base URL, for a DNS lookup: the scheme, any path and
// any port cut away. "https://ertale.com/tarik" -> "ertale.com". The old code
// deleted every slash instead and looked up "ertale.comtarik", which failed
// five times and cost ten seconds on every wake (unit #2's log, 2026-09-18).
void api_hostname(const char* url, char* out, size_t out_size);
