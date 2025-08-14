#ifndef PROTOTYPE_SYMBOL_H
#define PROTOTYPE_SYMBOL_H

#include "type.h"   // for Type enum
#include "prototype-token.h"  // for Token enum or struct

typedef enum {
    SYMBOL_TYPE,
    SYMBOL_NAME,
    SYMBOL_TOKEN
} SymbolType;

typedef struct {
    SymbolType kind;  // What kind of symbol this is
    union {
        Type type;       // Only valid if kind == SYMBOL_TYPE
        const char* name; // Only valid if kind == SYMBOL_NAME
        Token token;     // Only valid if kind == SYMBOL_TOKEN
    } value;
} Symbol;

#endif // SYMBOL_H
