# Lexer Testing

This directory contains test files for testing the Obsidian compiler lexer.

## Files

- `test-lexer.c` - Test lexer source code
- `test-lexer.mk` - Makefile for Unix/Linux/macOS testing
- `test-lexer.bat` - Windows batch file for testing

## Testing the Lexer

### Unix/Linux/macOS
```bash
cd build/testing
make -f test-lexer.mk test-lexer
```

### Windows
```batch
cd build\testing
test-lexer.bat
```

## What the Test Does

The test lexer will:

1. **Run full lexical analysis** on the specified `.obs` file
2. **Test individual components**:
   - `tokenize_inclusions()` - Parse include statements
   - `tokenize_prototypes()` - Parse function prototypes
   - `tokenize_global_vars()` - Parse global variable declarations
3. **Display results** showing all parsed tokens and symbols

## Test Output

The test will show:
- **INCLUSIONS**: All include paths found
- **PROTOTYPES**: Function prototypes with their tokens
- **GLOBAL VARIABLES**: Global variable declarations

## Example Usage

```bash
# Test on the sample input file
make -f test-lexer.mk test-lexer

# Clean test artifacts
make -f test-lexer.mk clean-test

# Show help
make -f test-lexer.mk help
```

## Requirements

- GCC compiler
- The lexer source code must compile successfully
- The input `.obs` file must exist and be readable

## Troubleshooting

- **Build errors**: Check that all source files compile
- **Runtime errors**: Verify the input file path is correct
- **Memory issues**: Ensure string utilities are working properly
