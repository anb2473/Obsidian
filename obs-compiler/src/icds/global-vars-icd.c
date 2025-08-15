#include "../../include/icds/global-vars-icd.h"
#include <stdlib.h>

void global_var_symbol_array_init(void *elt) {
    UT_array **arr_ptr = (UT_array**)elt;
    *arr_ptr = NULL;
}

void global_var_symbol_array_copy(void *dst, const void *src) {
    UT_array **dst_ptr = (UT_array**)dst;
    UT_array * const *src_ptr = (UT_array* const *)src;

    if (*src_ptr) {
        // Allocate and initialize new UT_array with same contents
        utarray_new(*dst_ptr, &global_var_symbol_icd);
        for (GlobalVarSymbol *s = (GlobalVarSymbol*)utarray_front(*src_ptr);
             s != NULL;
             s = (GlobalVarSymbol*)utarray_next(*src_ptr, s)) {
            utarray_push_back(*dst_ptr, s);
        }
    } else {
        *dst_ptr = NULL;
    }
}

void global_var_symbol_array_dtor(void *elt) {
    UT_array **arr_ptr = (UT_array**)elt;
    if (*arr_ptr) {
        utarray_free(*arr_ptr);
        *arr_ptr = NULL;
    }
}

UT_icd global_var_symbol_array_icd = {
    sizeof(UT_array*),
    global_var_symbol_array_init,
    global_var_symbol_array_copy,
    global_var_symbol_array_dtor
};
