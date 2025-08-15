#include "../../include/icds/global-var-symbol-icd.h"
#include <string.h>
#include <stdlib.h>

void global_var_symbol_init(void *elt) {
    GlobalVarSymbol *s = (GlobalVarSymbol*)elt;
    s->kind = GLOBAL_SYMBOL_TYPE; // default kind
    s->value.type = BYTE;  // default type
}

void global_var_symbol_copy(void *dst, const void *src) {
    const GlobalVarSymbol *s_src = (const GlobalVarSymbol*)src;
    GlobalVarSymbol *s_dst = (GlobalVarSymbol*)dst;
    s_dst->kind = s_src->kind;

    switch (s_src->kind) {
        case GLOBAL_SYMBOL_TYPE:
            s_dst->value.type = s_src->value.type;
            break;
        case GLOBAL_SYMBOL_NAME:
            if (s_src->value.name) {
                s_dst->value.name = strdup(s_src->value.name);
            } else {
                s_dst->value.name = NULL;
            }
            break;
        case GLOBAL_SYMBOL_TOKEN:
            s_dst->value.token = s_src->value.token;
            break;
    }
}

void global_var_symbol_dtor(void *elt) {
    GlobalVarSymbol *s = (GlobalVarSymbol*)elt;
    if (s->kind == GLOBAL_SYMBOL_NAME && s->value.name) {
        free((void*)s->value.name);  // Free strdup’ed string
    }
}

UT_icd global_var_symbol_icd = {
    sizeof(GlobalVarSymbol),
    global_var_symbol_init,
    global_var_symbol_copy,
    global_var_symbol_dtor
};
