#include "../../include/icds/fn-lines-array-icd.h"

void textsymbol_array_array_init(void *_elt) {
    UT_array *arr;
    utarray_new(arr, &fn_lines_array_icd);
    *(UT_array **)_elt = arr;
}

void textsymbol_array_array_copy(void *_dst, const void *_src) {
    UT_array *src = *(UT_array **)_src;
    UT_array *dst;
    utarray_new(dst, &fn_lines_array_icd);

    if (src) {
        utarray_concat(dst, src);
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
    sizeof(UT_array *),
    textsymbol_array_array_init,
    textsymbol_array_array_copy,
    textsymbol_array_array_dtor
};
