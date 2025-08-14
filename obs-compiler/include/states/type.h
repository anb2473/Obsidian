#ifndef TYPE_H
#define TYPE_H

typedef enum {
    BYTE,   // Unsigned byte
    CHR,    // Signed byte
    WRD,    // Unsigned short
    SHRT,   // Signed short
    DWRD,   // Unsigned int
    LNG,    // Signed int
    QWRD,   // Unsigned double
    DLNG,   // Signed double
    FLT,    // Float
    DBL,    // Double
    LDBL,   // Long Double
    PTR,    // Pointer (void*)
    HNDL,   // Handle (void* OR DWORD for Windows Handles)
} Type;

#endif