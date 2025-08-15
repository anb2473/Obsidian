#ifndef GLOBAL_VAR_SYMBOL_H
#define GLOBAL_VAR_SYMBOL_H

#include "type.h"   // for Type enum
#include "global-var-token.h"  // for Token enum or struct

typedef enum {
    GLOBAL_SYMBOL_TYPE,
    GLOBAL_SYMBOL_NAME,
    GLOBAL_SYMBOL_TOKEN
} GlobalVarSymbolType;

typedef struct {
    GlobalVarSymbolType kind;  // What kind of symbol this is
    union {
        Type type;       // Only valid if kind == SYMBOL_TYPE
        const char* name; // Only valid if kind == SYMBOL_NAME
        GlobalVarToken token;     // Only valid if kind == SYMBOL_TOKEN
    } value;
} GlobalVarSymbol;

#endif // SYMBOL_H
