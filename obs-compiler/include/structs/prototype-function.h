#ifndef PROTOTYPE_FUNCTION_H
#define PROTOTYPE_FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../states/type.h"
#include "../utils/utarray.h"

typedef struct {
    char* name;
    UT_array* param_types;
    Type return_type;
} PrototypeFunction;

#ifdef __cplusplus
}
#endif

#endif