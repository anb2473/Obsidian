#ifndef GLOBAL_VAR_SYMBOL_ICD_H
#define GLOBAL_VAR_SYMBOL_ICD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../states/global-var-symbol.h"  // Your Symbol definition
#include "../utils/utarray.h"

// Declarations for ICD functions
void global_var_symbol_init(void *elt);
void global_var_symbol_copy(void *dst, const void *src);
void global_var_symbol_dtor(void *elt);

// Extern UT_icd for Symbol
extern UT_icd global_var_symbol_icd;

#ifdef __cplusplus
}
#endif

#endif // GLOBAL_VAR_SYMBOL_ICD_H
