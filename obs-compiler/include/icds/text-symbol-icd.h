#ifndef TEXT_SYMBOL_ICD_H
#define TEXT_SYMBOL_ICD_H

#include "utarray.h"
#include "../states/text-symbol.h"

// init/copy/dtor functions for TextSymbol
void textsymbol_init(void *_elt);
void textsymbol_copy(void *_dst, const void *_src);
void textsymbol_dtor(void *_elt);

// ICD definition for UT_array
extern UT_icd text_symbol_icd;

#endif // TEXT_SYMBOL_ICD_H
