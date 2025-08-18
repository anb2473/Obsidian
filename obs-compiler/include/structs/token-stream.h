#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "../utils/utarray.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    UT_array* included_paths;
    UT_array* prototype_functions;
    UT_array* global_vars;
    UT_array* text_section;
} TokenStream;

#ifdef __cplusplus
}
#endif

#endif // TOKEN_STREAM_H
