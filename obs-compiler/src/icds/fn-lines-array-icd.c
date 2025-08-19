#include "../../include/icds/fn-lines-array-icd.h"
#include "../../include/icds/text-symbol-icd.h"

void textsymbol_array_array_init(void *_elt) {
    UT_array *arr = NULL;
    utarray_new(arr, &text_symbol_icd);
    *(UT_array **)_elt = arr;
}

void textsymbol_array_array_copy(void *_dst, const void *_src) {
    UT_array *src = *(UT_array **)_src;
    UT_array *dst = NULL;
    
    if (src) {
        utarray_new(dst, &text_symbol_icd);
        if (dst) {
            utarray_concat(dst, src);
        }
    }
    *(UT_array **)_dst = dst;
}

void textsymbol_array_array_dtor(void *_elt) {
    UT_array *arr = *(UT_array **)_elt;
    if (arr) {
        utarray_free(arr);
        *(UT_array **)_elt = NULL;
    }
}

UT_icd fn_lines_array_icd = {
    sizeof(UT_array *),  // Size of a pointer to UT_array
    textsymbol_array_array_init,
    textsymbol_array_array_copy,
    textsymbol_array_array_dtor
};
