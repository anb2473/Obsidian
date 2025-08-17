#ifndef FN_DECL_ICD_H
#define FN_DECL_ICD_H

#include "utarray.h"
#include "../structs/fn-decl.h"
#include "char-ptr-icd.h"
#include "fn-lines-array-icd.h"

void fndecl_init(void *_elt);
void fndecl_copy(void *_dst, const void *_src);
void fndecl_dtor(void *_elt);

extern UT_icd fn_decl_icd;

#endif // FN_DECL_ICD_H
