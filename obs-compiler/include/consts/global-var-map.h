#ifndef GLOBAL_VAR_MAP_H
#define GLOBAL_VAR_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../states/type.h"  // Make sure Type enum is included
#include <stdio.h>
#include "../states/global-var-token.h"

typedef struct {
    const char* name;
    GlobalVarToken type;
} GlobalVarMapEntry;

// Array of string → Type mappings
static const GlobalVarMapEntry global_var_map[] = {
    { "rod", TOKEN_CONST },
    { "bss", TOKEN_BSS },
    { "mut", TOKEN_MUTABLE },
};

// Number of entries in type_map
static const size_t global_var_count = sizeof(global_var_map)/sizeof(global_var_map[0]);

#ifdef __cplusplus
}
#endif

#endif // TYPE_MAP_H
