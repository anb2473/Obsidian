# Obsidian Compiler

A C-based compiler for the Obsidian language.

## String Management

The compiler now uses a robust string management system through the `StringBuffer` utility class located in `src/utils/str-utils.c` and `include/utils/str-utils.h`.

### StringBuffer Features

- **Safe string building**: Automatically manages memory allocation and expansion
- **Character-by-character appending**: Safe to append individual characters
- **String appending**: Efficiently append existing strings
- **Memory management**: Automatic cleanup and memory leak prevention
- **Bounds checking**: Prevents buffer overflows

### Key Functions

- `str_buffer_new(size_t capacity)`: Create a new string buffer
- `str_buffer_append_char(StringBuffer* buffer, char ch)`: Append a single character
- `str_buffer_append_str(StringBuffer* buffer, const char* str)`: Append a string
- `str_buffer_get_string(const StringBuffer* buffer)`: Get the current string content
- `str_buffer_duplicate(const StringBuffer* buffer)`: Create a copy of the string
- `str_buffer_clear(StringBuffer* buffer)`: Clear the buffer content
- `str_buffer_free(StringBuffer* buffer)`: Free the buffer and its memory

### Usage Example

```c
#include "include/utils/str-utils.h"

StringBuffer* buffer = str_buffer_new(64);
str_buffer_append_char(buffer, 'H');
str_buffer_append_char(buffer, 'e');
str_buffer_append_char(buffer, 'l');
str_buffer_append_char(buffer, 'l');
str_buffer_append_char(buffer, 'o');

const char* result = str_buffer_get_string(buffer); // "Hello"
char* copy = str_buffer_duplicate(buffer); // Create a copy

str_buffer_free(buffer); // Clean up
free(copy); // Clean up the copy
```

## Building

### Windows
```batch
build.bat
```

### Linux/macOS
```bash
make
```

## Testing

### Test String Utilities
```batch
test_str_utils.bat
```

### Test Full Compiler
```batch
build.bat
bin/obs-compiler.exe
```

## File Structure

```
obs-compiler/
├── include/
│   └── utils/
│       └── str-utils.h          # String utilities header
├── src/
│   ├── utils/
│   │   └── str-utils.c          # String utilities implementation
│   ├── lexer.c                  # Lexical analyzer (updated)
│   ├── parser.c                  # Parser
│   └── compiler.c                # Main compiler
├── build.bat                     # Windows build script
├── test_str_utils.bat           # String utilities test script
└── Makefile                      # Unix build system
```

## Recent Changes

- **Fixed string management**: Replaced unsafe `strcat` usage with `StringBuffer`
- **Added proper memory management**: Automatic cleanup and bounds checking
- **Improved lexer functions**: All tokenization functions now use safe string handling
- **Added comprehensive testing**: Test suite for string utilities
- **Cross-platform build support**: Windows batch files and Unix Makefile

## Dependencies

- GCC or compatible C compiler
- Standard C library (stdlib, string, stdio)
- uthash library (included in the project)
