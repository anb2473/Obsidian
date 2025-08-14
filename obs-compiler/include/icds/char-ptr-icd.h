#ifndef CHAR_PTR_ARRAY_H
#define CHAR_PTR_ARRAY_H

#include "utarray.h"

#ifdef __cplusplus
extern "C" {
#endif

extern UT_icd char_ptr_icd;   // ICD for char*
extern UT_array* char_array;  // the dynamic array

void char_array_init(void);
void char_array_push(char* str);
void char_array_free(void);

#ifdef __cplusplus
}
#endif

#endif // CHAR_PTR_ARRAY_H
