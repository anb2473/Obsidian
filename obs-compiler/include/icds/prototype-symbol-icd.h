#ifndef PROTOTYPE_SYMBOL_ICD_H
#define PROTOTYPE_SYMBOL_ICD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../states/prototype-symbol.h"
#include "../utils/utarray.h"

// Function declarations for UT_icd
void prototype_symbol_init(void *elt);
void prototype_copy(void *dst, const void *src);
void prototype_dtor(void *elt);

// UT_icd for Symbol
extern UT_icd prototype_symbol_icd;

#ifdef __cplusplus
}
#endif

#endif // PROTOTYPE_SYMBOL_ICD_H
