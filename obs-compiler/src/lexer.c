#include <stdio.h>
#include <stdbool.h>
#include "../include/utils/utarray.h"

// Include states
#include "../include/states/prototype-symbol.h"

// Include icds
#include "../include/icds/char-ptr-icd.h"
#include "../include/icds/prototype-symbol-icd.h"
#include "../include/icds/prototype-functions-icd.h"

// Include type map
#include "../include/consts/type-map.h"

// Include limits
#include <limits.h>  // for PATH_MAX
#ifndef PATH_MAX
#define PATH_MAX 4096   // fallback max path length
#endif

bool check_seek (FILE* obs_file, char* target_str) {
    int ch;  // Use int to hold EOF safely
    char* p = target_str;
    while ((ch = fgetc(obs_file)) != EOF && *p != '\0') {
        if (ch != *p) {
            return false;
        }
        p++;
    }
    return *p == '\0';  // Make sure that the check did not just reach the EOF
}

UT_array* tokenize_inclusions (FILE* obs_file) {
    UT_array* path_array = NULL;
    utarray_new(path_array, &char_ptr_icd);

    char current_path[PATH_MAX];
    size_t idx = 0;

    int ch;
    while ((ch = fgetc(obs_file)) != EOF) {
        if (ch == '-') {
            long pos = ftell(obs_file);
            if (check_seek(obs_file, "--")) {
                break;  // end of imports
            } else {
                fseek(obs_file, pos, SEEK_SET);  // rewind
            }
        } else if (ch == '\n') {
            if (idx > 0) {  // only add non-empty paths
                current_path[idx] = '\0';
                char* stored_path = strdup(current_path);
                utarray_push_back(path_array, &stored_path);
                idx = 0;  // reset for next path
            }
        } else {
            if (idx < PATH_MAX - 1) {  // leave room for null terminator
                current_path[idx++] = (char)ch;
            }
        }
    }

    // Add last path if file doesn't end with newline
    if (idx > 0) {
        current_path[idx] = '\0';
        char* stored_path = strdup(current_path);
        utarray_push_back(path_array, &stored_path);
    }

    return path_array;
}

int move_fptr_to_section_end (FILE* obs_file) {
    int ch;
    // Skip all '-' (until you reach next section)
    while ((ch = fgetc(obs_file)) != EOF && ch == '-') {}  
}

Type check_for_type (FILE* obs_file) {
    for (size_t i = 0; i < type_map_count; ++i) {
        if (check_seek(obs_file, type_map[i].name)) {
            return &type_map[i].type;  // return pointer to the Type
        }
    }
    return NULL;  // no match
}

UT_array* tokenize_prototypes (FILE* obs_file) {  // name ( param1_type, param2_type ) -> return_type
    // Array of current prototype function token stream
    UT_array* prototype_functions;
    utarray_new(prototype_functions, &prototype_functions_icd);
        
    // Prototype function token stream
    UT_array* current_prototype_function_tokens;
    utarray_new(current_prototype_function_tokens, &symbol_icd);

    char* current_token;

    int ch;
    while ((ch = fgetc(obs_file)) != EOF) {
        switch (ch) {
            case '\n':
                utarray_push_back(prototype_functions, current_prototype_function_tokens);
                utarray_new(current_prototype_function_tokens, &symbol_icd);
            case '(': // open brace (open parameters)
                if (strlen(current_token) == 0) {
                    Symbol new_symbol = {
                        .kind = SYMBOL_NAME,
                        .value = current_token,
                    };
                    utarray_push_back(current_prototype_function_tokens, &new_symbol);
                }
                Symbol new_symbol = {
                    .kind = SYMBOL_TOKEN,
                    .value = { .token = TOKEN_OPEN_BRACE }
                };
                utarray_push_back(current_prototype_function_tokens, &new_symbol);
            case ')':   // close brace (end parameters)
                Symbol new_symbol = {
                    .kind = SYMBOL_TOKEN,
                    .value = { .token = TOKEN_CLOSE_BRACE }
                };
                utarray_push_back(current_prototype_function_tokens, &new_symbol);
            case '-':   // return type or section end
                if (check_seek(obs_file, '--')) {
                    utarray_push_back(prototype_functions, current_prototype_function_tokens);
                    free(current_prototype_function_tokens);
                    break;
                }
                if (check_seek(obs_file, '>')) {
                    Symbol new_symbol = {
                        .kind = SYMBOL_TOKEN,
                        .value = { .token =  TOKEN_RET }
                    };
                    utarray_push_back(current_prototype_function_tokens, &new_symbol);
                }
            case '.':   // type
                Type type = check_for_type(obs_file);
                if (type != NULL) {
                    Symbol new_symbol = {
                        .kind = SYMBOL_TYPE,
                        .value = type
                    };
                    utarray_push_back(current_prototype_function_tokens, &new_symbol);
                }
        }
    }
    return prototype_functions;
}

int lexical_analysis (char* obs_path) {
    /*
        Return Codes:
        1 -- Failed to open .obs file
    */

    FILE* obs_file = NULL;
    fopen(obs_path, obs_file);
    if (obs_file == NULL) {
        perror("Failed to open .obs file");
        return 1;
    }

    // Get UT_array of paths
    UT_array* included_paths = tokenize_inclusions(obs_file);

    move_fptr_to_section_end(obs_file);

    // Get UT_array of prototype tokens
    UT_array* prototype_functions = tokenize_prototypes(obs_file);
}