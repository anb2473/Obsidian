#ifndef PROTOTYPE_SYMBOL_ICD_H
#define PROTOTYPE_SYMBOL_ICD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../states/prototype-symbol.h"
#include "../utils/utarray.h"

// Function declarations for UT_icd
void symbol_init(void *elt);
void symbol_copy(void *dst, const void *src);
void symbol_dtor(void *elt);

// UT_icd for Symbol
extern UT_icd symbol_icd;

#ifdef __cplusplus
}
#endif

#endif // PROTOTYPE_SYMBOL_ICD_H
