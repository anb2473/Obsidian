#ifndef GLOBAL_VAR_SYMBOL_ARRAY_ICD_H
#define GLOBAL_VAR_SYMBOL_ARRAY_ICD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "global-var-symbol-icd.h"  // for global_var_symbol_icd
#include "../utils/utarray.h"

// Declarations for UT_array* of UT_array(Symbol) functions
void global_var_symbol_array_init(void *elt);
void global_var_symbol_array_copy(void *dst, const void *src);
void global_var_symbol_array_dtor(void *elt);

// Extern UT_icd for UT_array* of Symbols
extern UT_icd global_var_symbol_array_icd;

#ifdef __cplusplus
}
#endif

#endif // GLOBAL_VAR_SYMBOL_ARRAY_ICD_H
