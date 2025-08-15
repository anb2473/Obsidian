#define _CONSOLE
#undef _WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/utils/utarray.h"
#include "../../include/structs/token-stream.h"
#include "../../include/states/prototype-symbol.h"
#include "../../include/states/global-var-symbol.h"
#include "../../include/states/global-var-token.h"

// Forward declaration from lexer.c
extern TokenStream lexical_analysis(const char* obs_path);

void print_inclusions(UT_array* inclusions) {
    if (!inclusions) {
        printf("No inclusions found\n");
        return;
    }
    
    printf("=== INCLUSIONS ===\n");
    char** path;
    for (path = (char**)utarray_front(inclusions);
         path != NULL;
         path = (char**)utarray_next(inclusions, path)) {
        printf("Include: %s\n", *path);
    }
    printf("\n");
}

void print_prototypes(UT_array* prototypes) {
    if (!prototypes) {
        printf("No prototypes found\n");
        return;
    }
    
    printf("=== PROTOTYPES ===\n");
    UT_array** prototype;
    for (prototype = (UT_array**)utarray_front(prototypes);
         prototype != NULL;
         prototype = (UT_array**)utarray_next(prototypes, prototype)) {
        printf("Prototype function:\n");

        PrototypeSymbol* symbol;
        for (symbol = (PrototypeSymbol*)utarray_front(*prototype);
             symbol != NULL;
             symbol = (PrototypeSymbol*)utarray_next(*prototype, symbol)) {
            switch (symbol->kind) {
                case SYMBOL_NAME:
                    printf("  NAME: %s\n", symbol->value.name);
                    break;
                case SYMBOL_TYPE:
                    printf("  TYPE: %d\n", symbol->value.type);
                    break;
                case SYMBOL_TOKEN:
                    printf("  TOKEN: %d\n", symbol->value.token);
                    break;
            }
        }
        printf("\n");
    }
}

void print_global_vars(UT_array* global_vars) {
    if (!global_vars) {
        printf("No global variables found\n");
        return;
    }
    
    printf("=== GLOBAL VARIABLES ===\n");
    UT_array** global_var;
    for (global_var = (UT_array**)utarray_front(global_vars);
         global_var != NULL;
         global_var = (UT_array**)utarray_next(global_vars, global_var)) {
        printf("Global variable:\n");

        GlobalVarSymbol* symbol;
        for (symbol = (GlobalVarSymbol*)utarray_front(*global_var);
             symbol != NULL;
             symbol = (GlobalVarSymbol*)utarray_next(*global_var, symbol)) {
            switch (symbol->kind) {
                case GLOBAL_SYMBOL_NAME:
                    printf("  NAME: %s\n", symbol->value.name);
                    break;
                case GLOBAL_SYMBOL_TYPE:
                    printf("  TYPE: %d\n", symbol->value.type);
                    break;
                case GLOBAL_SYMBOL_TOKEN:
                    printf("  TOKEN: %d\n", symbol->value.token);
                    break;
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <obs_file_path>\n", argv[0]);
        return 1;
    }
    
    const char* obs_path = argv[1];
    printf("Testing lexer on file: %s\n\n", obs_path);
    
    printf("Running lexical analysis...\n");
    TokenStream stream = lexical_analysis(obs_path);
    
    // Print all the tokenized data
    printf("\nLexical analysis completed!\n\n");
    print_inclusions(stream.included_paths);
    print_prototypes(stream.prototype_functions);
    print_global_vars(stream.global_vars);
    
    printf("All tests completed!\n");
    return 0;
}