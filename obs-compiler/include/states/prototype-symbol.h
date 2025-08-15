#ifndef PROTOTYPE_SYMBOL_H
#define PROTOTYPE_SYMBOL_H

#include "type.h"   // for Type enum
#include "prototype-token.h"  // for Token enum or struct

typedef enum {
    SYMBOL_TYPE,
    SYMBOL_NAME,
    SYMBOL_TOKEN
} PrototypeSymbolType;

typedef struct {
    PrototypeSymbolType kind;  // What kind of symbol this is
    union {
        Type type;       // Only valid if kind == SYMBOL_TYPE
        const char* name; // Only valid if kind == SYMBOL_NAME
        PrototypeToken token;     // Only valid if kind == SYMBOL_TOKEN
    } value;
} PrototypeSymbol;

#endif // SYMBOL_H
