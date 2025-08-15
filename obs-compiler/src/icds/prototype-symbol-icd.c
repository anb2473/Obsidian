#include "../../include/icds/prototype-symbol-icd.h"
#include <stdlib.h>
#include <string.h>

// Initialize a Symbol
void prototype_symbol_init(void *elt) {
    PrototypeSymbol *s = (PrototypeSymbol*)elt;
    s->kind = SYMBOL_TYPE; // default kind
    s->value.type = BYTE;  // default type
}

// Copy a Symbol
void prototype_symbol_copy(void *dst, const void *src) {
    const PrototypeSymbol *s_src = (const PrototypeSymbol*)src;
    PrototypeSymbol *s_dst = (PrototypeSymbol*)dst;
    s_dst->kind = s_src->kind;

    switch (s_src->kind) {
        case SYMBOL_TYPE:
            s_dst->value.type = s_src->value.type;
            break;
        case SYMBOL_NAME:
            if (s_src->value.name) {
                s_dst->value.name = strdup(s_src->value.name);
            } else {
                s_dst->value.name = NULL;
            }
            break;
        case SYMBOL_TOKEN:
            s_dst->value.token = s_src->value.token;
            break;
    }
}

// Destroy a Symbol
void prototype_symbol_dtor(void *elt) {
    PrototypeSymbol *s = (PrototypeSymbol*)elt;
    if (s->kind == SYMBOL_NAME && s->value.name) {
        free((void*)s->value.name);  // free strdup’ed string
    }
}

// The actual ICD variable
UT_icd prototype_symbol_icd = {
    sizeof(PrototypeSymbol),
    prototype_symbol_init,
    prototype_symbol_copy,
    prototype_symbol_dtor
};