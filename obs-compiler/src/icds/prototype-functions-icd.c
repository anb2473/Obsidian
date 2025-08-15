#include "../../include/icds/prototype-functions-icd.h"

// Initialize a UT_array* pointer
void prototype_functions_init(void *elt) {
    UT_array **arr_ptr = (UT_array**)elt;
    *arr_ptr = NULL;
}

// Copy a UT_array* pointer
void prototype_functions_copy(void *dst, const void *src) {
    UT_array **dst_ptr = (UT_array**)dst;
    UT_array * const *src_ptr = (UT_array* const *)src;

    if (*src_ptr) {
        // Create a new UT_array and copy Symbols
        *dst_ptr = (UT_array*)malloc(sizeof(UT_array));
        utarray_init(*dst_ptr, &prototype_symbol_icd);
        for (PrototypeSymbol *s = (PrototypeSymbol*)utarray_front(*src_ptr);
             s != NULL;
             s = (PrototypeSymbol*)utarray_next(*src_ptr, s)) {
            utarray_push_back(*dst_ptr, s);
        }
    } else {
        *dst_ptr = NULL;
    }
}

// Destroy a UT_array* pointer
void prototype_functions_dtor(void *elt) {
    UT_array **arr_ptr = (UT_array**)elt;
    if (*arr_ptr) {
        utarray_free(*arr_ptr);
        *arr_ptr = NULL;
    }
}

// ICD for a UT_array* of Symbol arrays
UT_icd prototype_functions_icd = {
    sizeof(UT_array*),
    prototype_functions_init,
    prototype_functions_copy,
    prototype_functions_dtor
};
