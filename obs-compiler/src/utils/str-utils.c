#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../include/utils/str-utils.h"

StringBuffer* str_buffer_new(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 64; // Default capacity
    }
    
    StringBuffer* buffer = malloc(sizeof(StringBuffer));
    if (!buffer) {
        return NULL;
    }
    
    buffer->buffer = malloc(initial_capacity);
    if (!buffer->buffer) {
        free(buffer);
        return NULL;
    }
    
    buffer->capacity = initial_capacity;
    buffer->length = 0;
    buffer->buffer[0] = '\0';
    
    return buffer;
}

bool str_buffer_append_char(StringBuffer* buffer, char ch) {
    if (!buffer || !buffer->buffer) {
        return false;
    }
    
    // Check if we need to expand capacity
    if (buffer->length + 2 > buffer->capacity) { // +2 for char + null terminator
        size_t new_capacity = buffer->capacity * 2;
        char* new_buffer = realloc(buffer->buffer, new_capacity);
        if (!new_buffer) {
            return false;
        }
        buffer->buffer = new_buffer;
        buffer->capacity = new_capacity;
    }
    
    buffer->buffer[buffer->length] = ch;
    buffer->length++;
    buffer->buffer[buffer->length] = '\0';
    
    return true;
}

bool str_buffer_append_str(StringBuffer* buffer, const char* str) {
    if (!buffer || !buffer->buffer || !str) {
        return false;
    }
    
    size_t str_len = strlen(str);
    if (str_len == 0) {
        return true;
    }
    
    // Check if we need to expand capacity
    if (buffer->length + str_len + 1 > buffer->capacity) {
        size_t new_capacity = buffer->capacity;
        while (new_capacity < buffer->length + str_len + 1) {
            new_capacity *= 2;
        }
        
        char* new_buffer = realloc(buffer->buffer, new_capacity);
        if (!new_buffer) {
            return false;
        }
        buffer->buffer = new_buffer;
        buffer->capacity = new_capacity;
    }
    
    strcpy(buffer->buffer + buffer->length, str);
    buffer->length += str_len;
    
    return true;
}

const char* str_buffer_get_string(const StringBuffer* buffer) {
    if (!buffer || !buffer->buffer) {
        return "";
    }
    return buffer->buffer;
}

void str_buffer_clear(StringBuffer* buffer) {
    if (buffer && buffer->buffer) {
        buffer->length = 0;
        buffer->buffer[0] = '\0';
    }
}

void str_buffer_free(StringBuffer* buffer) {
    if (buffer) {
        if (buffer->buffer) {
            free(buffer->buffer);
        }
        free(buffer);
    }
}

char* str_buffer_duplicate(const StringBuffer* buffer) {
    if (!buffer || !buffer->buffer) {
        return NULL;
    }
    
    char* copy = malloc(buffer->length + 1);
    if (copy) {
        strcpy(copy, buffer->buffer);
    }
    return copy;
}

bool str_buffer_is_empty(const StringBuffer* buffer) {
    return !buffer || buffer->length == 0;
}

void str_buffer_reset(StringBuffer* buffer) {
    str_buffer_clear(buffer);
}
