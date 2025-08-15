#ifndef CHAR_PTR_ICD_H
#define CHAR_PTR_ICD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../utils/utarray.h"

void char_ptr_dtor(void *elt);
void char_ptr_copy(void *dst, const void *src);
void char_ptr_init(void *elt);

extern UT_icd char_ptr_icd;

#ifdef __cplusplus
}
#endif

#endif // CHAR_PTR_ICD_H
