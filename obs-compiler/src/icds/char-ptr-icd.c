#include <stdlib.h>
#include <string.h>

#include "../../include/icds/char-ptr-icd.h"

// Initialize a char* (set to NULL by default)
void char_ptr_init(void *elt) {
    char **p = (char **)elt;
    *p = NULL;
}

// Copy a char*
void char_ptr_copy(void *dst, const void *src) {
    char **d = (char **)dst;
    char *const *s = (char *const *)src;
    if (*s) {
        *d = strdup(*s);  // allocate a new copy
    } else {
        *d = NULL;
    }
}

// Destroy a char*
void char_ptr_dtor(void *elt) {
    char **p = (char **)elt;
    if (*p) {
        free(*p);
        *p = NULL;
    }
}

// The ICD variable that other files can reference
UT_icd char_ptr_icd = {
    sizeof(char*),
    char_ptr_init,
    char_ptr_copy,
    char_ptr_dtor
};
