#include <string.h>
#include <stdlib.h>
#include "../../include/icds/text-symbol-icd.h"

void textsymbol_init(void *_elt) {
    TextSymbol *elt = (TextSymbol *)_elt;
    elt->kind = 0;
    elt->value.name = NULL; // safe default
}

void textsymbol_copy(void *_dst, const void *_src) {
    const TextSymbol *src = (const TextSymbol *)_src;
    TextSymbol *dst = (TextSymbol *)_dst;

    *dst = *src;  // shallow copy first
    if (src->kind == TEXT_SYMBOL_NAME && src->value.name) {
        dst->value.name = strdup(src->value.name);  // deep copy name
    }
}

void textsymbol_dtor(void *_elt) {
    TextSymbol *elt = (TextSymbol *)_elt;
    if (elt->kind == TEXT_SYMBOL_NAME && elt->value.name) {
        free((void*)elt->value.name);  // free strdup’d string
        elt->value.name = NULL;
    }
}

UT_icd text_symbol_icd = {
    sizeof(TextSymbol),
    textsymbol_init,
    textsymbol_copy,
    textsymbol_dtor
};
