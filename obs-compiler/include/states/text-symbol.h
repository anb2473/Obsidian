#ifndef GLOBAL_VAR_SYMBOL_H
#define GLOBAL_VAR_SYMBOL_H

#include "type.h"   // for Type enum
#include "text-token.h"  // for Token enum or struct

typedef enum {
    TEXT_SYMBOL_TYPE,
    TEXT_SYMBOL_NAME,
    TEXT_SYMBOL_TOKEN
} TextSymbolType;

typedef struct {
    TextSymbolType kind;  // What kind of symbol this is
    union {
        Type type;       // Only valid if kind == SYMBOL_TYPE
        const char* name; // Only valid if kind == SYMBOL_NAME
        TextToken token;     // Only valid if kind == SYMBOL_TOKEN
    } value;
} TextSymbol;

#endif // SYMBOL_H
