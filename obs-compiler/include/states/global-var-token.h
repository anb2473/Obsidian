#ifndef GLOBAL_VAR_TOKEN_H
#define GLOBAL_VAR_TOKEN_H

// Token enum for your language
typedef enum {
    TOKEN_CONST,     // &rod (Read Only Data)
    TOKEN_BSS,       // &bss (Block Started by Symbol / Uninitialized)
    TOKEN_MUTABLE,   // &mut (mutable)
    TOKEN_EQ,        // =
    TOKEN_OPEN_STR,  // "
    TOKEN_CLOSE_STR, // "
    TOKEN_FN_POINTER, // &fn
    TOKEN_VAR_POINTER, // &var
} GlobalVarToken;

#endif // TOKEN_H
