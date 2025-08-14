#ifndef TYPE_MAP_H
#define TYPE_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../states/type.h"  // Make sure Type enum is included
#include <stdio.h>

typedef struct {
    const char* name;
    Type type;
} TypeMapEntry;

// Array of string → Type mappings
static const TypeMapEntry type_map[] = {
    { "byte", BYTE },
    { "chr",  CHR  },
    { "wrd",  WRD  },
    { "shrt", SHRT },
    { "dwrd", DWRD },
    { "lng",  LNG  },
    { "qwrd", QWRD },
    { "dlng", DLNG },
    { "flt",  FLT  },
    { "dbl",  DBL  },
    { "ldbl", LDBL },
    { "ptr",  PTR  },
    { "hndl", HNDL }
};

// Number of entries in type_map
static const size_t type_map_count = sizeof(type_map)/sizeof(type_map[0]);

#ifdef __cplusplus
}
#endif

#endif // TYPE_MAP_H
