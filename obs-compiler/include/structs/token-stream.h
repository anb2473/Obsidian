#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "../utils/utarray.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    UT_array* included_paths;
    UT_array* prototype_functions;
} TokenStream;

#ifdef __cplusplus
}
#endif

#endif // TOKEN_STREAM_H
