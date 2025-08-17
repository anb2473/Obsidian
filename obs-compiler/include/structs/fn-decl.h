#ifndef FN_DECL_H
#define FN_DECL_H

#include "../../include/utils/utarray.h"
#include "../states/type.h"

typedef struct {
    char* name;
    UT_array* args;
    Type type;
    UT_array* fn_lines;
} FnDecl;

#endif