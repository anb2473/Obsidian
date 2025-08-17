#ifndef TEXT_SYMBOL_ARRAY_ARRAY_ICD_H
#define TEXT_SYMBOL_ARRAY_ARRAY_ICD_H

#include "utarray.h"

// init/copy/dtor for UT_array<UT_array<TextSymbol>>
void textsymbol_array_array_init(void *_elt);
void textsymbol_array_array_copy(void *_dst, const void *_src);
void textsymbol_array_array_dtor(void *_elt);

extern UT_icd fn_lines_array_icd;

#endif // TEXT_SYMBOL_ARRAY_ARRAY_ICD_H
