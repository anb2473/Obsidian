#include "../../include/icds/fn-decl-icd.h"
#include <stdlib.h>
#include <string.h>

void fndecl_init(void *_elt) {
    FnDecl *fn = (FnDecl *)_elt;
    fn->name = NULL;
    fn->type = 0;

    fn->args = NULL;
    fn->fn_lines = NULL;

    utarray_new(fn->args, &char_ptr_icd);
    utarray_new(fn->fn_lines, &fn_lines_array_icd);
}

void fndecl_copy(void *_dst, const void *_src) {
    FnDecl *dst = (FnDecl *)_dst;
    const FnDecl *src = (const FnDecl *)_src;

    // Copy name
    dst->name = src->name ? strdup(src->name) : NULL;

    // Copy type
    dst->type = src->type;

    // Copy args
    if (src->args) {
        utarray_new(dst->args, &char_ptr_icd);
        utarray_concat(dst->args, src->args);
    } else {
        dst->args = NULL;
    }

    // Copy fn_lines
    if (src->fn_lines) {
        utarray_new(dst->fn_lines, &fn_lines_array_icd);
        utarray_concat(dst->fn_lines, src->fn_lines);
    } else {
        dst->fn_lines = NULL;
    }
}

void fndecl_dtor(void *_elt) {
    FnDecl *fn = (FnDecl *)_elt;

    if (fn->name) {
        free(fn->name);
        fn->name = NULL;
    }
    if (fn->args) {
        utarray_free(fn->args);
        fn->args = NULL;
    }
    if (fn->fn_lines) {
        utarray_free(fn->fn_lines);
        fn->fn_lines = NULL;
    }
}

UT_icd fn_decl_icd = {
    sizeof(FnDecl),
    fndecl_init,
    fndecl_copy,
    fndecl_dtor
};
