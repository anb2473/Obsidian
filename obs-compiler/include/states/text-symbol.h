#ifndef TEXT_SYMBOL_H
#define TEXT_SYMBOL_H

#include "type.h"   // for Type enum
#include "text-token.h"  // for Token enum or struct

typedef enum {
    TEXT_SYMBOL_TYPE,
    TEXT_SYMBOL_REG,
    TEXT_SYMBOL_TOKEN
} TextSymbolType;

typedef struct {
    TextSymbolType kind;  // What kind of symbol this is
    union {
        Type type;       // Only valid if kind == TEXT_SYMBOL_TYPE
        const char* reg; // Only valid if kind == TEXT_SYMBOL_REG
        TextToken token;     // Only valid if kind == TEXT_SYMBOL_TOKEN
    } value;
} TextSymbol;

#endif // SYMBOL_H
