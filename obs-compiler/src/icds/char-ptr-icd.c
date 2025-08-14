#include "utarray.h"
#include <string.h>
#include <stdlib.h>

// Include header file to expose functions
#include "../../include/icds/char-ptr-icd.h"

// ICD for char* (UTARRAY)
void charptr_init(void *elt) {
    *(char**)elt = NULL;
}

void charptr_copy(void *dst, const void *src) {
    const char *s = *(char**)src;
    if (s) {
        *(char**)dst = strdup(s); // deep copy string
    } else {
        *(char**)dst = NULL;
    }
}

void charptr_dtor(void *elt) {
    char *s = *(char**)elt;
    if (s) free(s);
}

UT_icd charptr_icd = { sizeof(char*), charptr_init, charptr_copy, charptr_dtor };
