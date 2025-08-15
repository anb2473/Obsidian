#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stddef.h>
#include <stdbool.h>

// String buffer structure for safe string building
typedef struct {
    char* buffer;
    size_t capacity;
    size_t length;
} StringBuffer;

// Initialize a string buffer with given capacity
StringBuffer* str_buffer_new(size_t initial_capacity);

// Append a character to the string buffer
bool str_buffer_append_char(StringBuffer* buffer, char ch);

// Append a string to the string buffer
bool str_buffer_append_str(StringBuffer* buffer, const char* str);

// Get the current string content
const char* str_buffer_get_string(const StringBuffer* buffer);

// Clear the buffer content (reset length to 0)
void str_buffer_clear(StringBuffer* buffer);

// Free the string buffer
void str_buffer_free(StringBuffer* buffer);

// Create a copy of the current string
char* str_buffer_duplicate(const StringBuffer* buffer);

// Check if buffer is empty
bool str_buffer_is_empty(const StringBuffer* buffer);

// Reset buffer to empty state
void str_buffer_reset(StringBuffer* buffer);

#endif // STR_UTILS_H
