#ifndef PROTOTYPE_FUNCTIONS_ICD_H
#define PROTOTYPE_FUNCTIONS_ICD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "../utils/utarray.h"
#include "prototype-symbol-icd.h"

// Function declarations
void prototype_functions_init(void *elt);
void prototype_functions_copy(void *dst, const void *src);
void prototype_functions_dtor(void *elt);

// ICD for a UT_array* of Symbol arrays
extern UT_icd prototype_functions_icd;

#ifdef __cplusplus
}
#endif

#endif // PROTOTYPE_FUNCTIONS_ICD_H
