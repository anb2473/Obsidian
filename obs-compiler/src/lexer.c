#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../include/utils/utarray.h"
#include "../include/utils/str-utils.h"

// Include structs
#include "../include/structs/token-stream.h"

// Include states
#include "../include/states/prototype-symbol.h"
#include "../include/states/global-var-symbol.h"
#include "../include/states/global-var-token.h"

// Include icds
#include "../include/icds/char-ptr-icd.h"
#include "../include/icds/prototype-symbol-icd.h"
#include "../include/icds/prototype-functions-icd.h"
#include "../include/icds/global-var-symbol-icd.h"
#include "../include/icds/global-vars-icd.h"

// Include type map
#include "../include/consts/type-map.h"

// Include global bar map
#include "../include/consts/global-var-map.h"

// Include limits
#include <limits.h>  // for PATH_MAX
#ifndef PATH_MAX
#define PATH_MAX 4096   // fallback max path length
#endif

bool check_seek (FILE* obs_file, const char* target_str) {
    long int pos = ftell(obs_file);
    int ch;
    const char* p = target_str;
    while ((ch = fgetc(obs_file)) != EOF && *p != '\0') {
        if (ch != *p) {
            fseek(obs_file, pos, SEEK_SET);
            return false;
        }
        p++;
    }
    if (*p != '\0') {
        fseek(obs_file, pos, SEEK_SET);
        return false;
    }
    return true;
}

UT_array* tokenize_inclusions (FILE* obs_file) {
    UT_array* path_array = NULL;
    utarray_new(path_array, &char_ptr_icd);

    StringBuffer* current_path = str_buffer_new(PATH_MAX);
    if (!current_path) {
        return path_array;
    }

    bool in_comment = false;

    int ch;
    while ((ch = fgetc(obs_file)) != EOF) {
        if (ch == '-' && !in_comment) {
            int next_ch = fgetc(obs_file);
            if (next_ch == '-') {
                break;  // end of imports
            } else {
                ungetc(next_ch, obs_file);
            }
        } else if (ch == '\n') {
            in_comment = false;
            if (!str_buffer_is_empty(current_path)) {  // only add non-empty paths
                char* stored_path = str_buffer_duplicate(current_path);
                if (stored_path) {
                    utarray_push_back(path_array, &stored_path);
                }
                str_buffer_clear(current_path);
            }
        } else if (ch == ';') {
            in_comment = true;
        } else if (!in_comment) {
            str_buffer_append_char(current_path, (char)ch);
        }
    }


    // Add last path if file doesn't end with newline
    if (!str_buffer_is_empty(current_path)) {
        char* stored_path = str_buffer_duplicate(current_path);
        if (stored_path) {
            utarray_push_back(path_array, &stored_path);
        }
    }

    str_buffer_free(current_path);
    return path_array;
}

int move_fptr_to_section_end (FILE* obs_file) {
    int ch;
    // Skip all '-' (until you reach next section)
    while ((ch = fgetc(obs_file)) != EOF && ch == '-') {}
    
    // Skip whitespace after dashes
    while ((ch = fgetc(obs_file)) != EOF && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')) {}
    
    // Put back the last character if it wasn't whitespace
    if (ch != EOF) {
        ungetc(ch, obs_file);
    }
    
    return 0;
}

Type* check_for_type (FILE* obs_file) {
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
    utarray_new(current_prototype_function_tokens, &prototype_symbol_icd);

    StringBuffer* current_token = str_buffer_new(64);
    if (!current_token) {
        return prototype_functions;
    }

    bool in_comment = false;
    long int pos;

    int ch;
    while ((ch = fgetc(obs_file)) != EOF) {
        switch (ch) {
            case '\n':
                if (utarray_len(current_prototype_function_tokens) != 0) {
                    utarray_push_back(prototype_functions, &current_prototype_function_tokens);
                }
                utarray_new(current_prototype_function_tokens, &prototype_symbol_icd);
                str_buffer_clear(current_token);
                in_comment = false;
                break;
            case '(': // open brace (open parameters)
                if (!in_comment && !str_buffer_is_empty(current_token)) {
                    char* token_str = str_buffer_duplicate(current_token);
                    if (token_str) {
                        PrototypeSymbol new_symbol = {
                            .kind = SYMBOL_NAME,
                            .value = { .name = token_str },
                        };
                        utarray_push_back(current_prototype_function_tokens, &new_symbol);
                    }
                }
                PrototypeSymbol new_symbol = {
                    .kind = SYMBOL_TOKEN,
                    .value = { .token = TOKEN_OPEN_BRACE }
                };
                utarray_push_back(current_prototype_function_tokens, &new_symbol);
                break;
            case ')':   // close brace (end parameters)
                if (!in_comment) {
                    PrototypeSymbol new_symbol2 = {
                        .kind = SYMBOL_TOKEN,
                        .value = { .token = TOKEN_CLOSE_BRACE }
                    };
                    utarray_push_back(current_prototype_function_tokens, &new_symbol2);
                    break;
                }
            case '-':   // return type or section end
                if (in_comment) {
                    continue;
                }
                int next_ch = fgetc(obs_file);
                if (next_ch == '-') {
                    if (utarray_len(current_prototype_function_tokens) != 0) {
                        utarray_push_back(prototype_functions, &current_prototype_function_tokens);
                    }
                    str_buffer_free(current_token);
                    return prototype_functions;
                } else if (next_ch == '>') {
                    PrototypeSymbol new_symbol3 = {
                        .kind = SYMBOL_TOKEN,
                        .value = { .token = TOKEN_RET }
                    };
                    utarray_push_back(current_prototype_function_tokens, &new_symbol3);
                } else {
                    ungetc(next_ch, obs_file);
                }
                break;
            case '.':   // type
                if (in_comment) {
                    continue;
                }
                Type* type = check_for_type(obs_file);
                if (type != NULL) {
                    PrototypeSymbol new_symbol4 = {
                        .kind = SYMBOL_TYPE,
                        .value = { .type = *type }
                    };
                    utarray_push_back(current_prototype_function_tokens, &new_symbol4);
                }
                break;

            case ' ':
                if (!in_comment && !str_buffer_is_empty(current_token)) {
                    char* token_str = str_buffer_duplicate(current_token);
                    if (token_str) {
                        PrototypeSymbol new_symbol5 = {
                            .kind = SYMBOL_NAME,
                            .value = { .name = token_str }
                        };
                        utarray_push_back(current_prototype_function_tokens, &new_symbol5);
                        str_buffer_clear(current_token);
                    }
                }
                break;
            case ';':
                in_comment = true;
            default:
                if (in_comment || ch == ',') {
                    continue;
                }
                str_buffer_append_char(current_token, (char)ch);
                break;
        }
    }
    
    if (utarray_len(current_prototype_function_tokens) != 0) {
        utarray_push_back(prototype_functions, &current_prototype_function_tokens);
    }
    str_buffer_free(current_token);
    return prototype_functions;
}

GlobalVarToken* check_for_global_var (FILE* obs_file) {
    for (size_t i = 0; i < global_var_count; ++i) {
        if (check_seek(obs_file, global_var_map[i].name)) {
            return &global_var_map[i].type;  // return pointer to the Global Var
        }
    }
    return NULL;  // no match
}

UT_array* tokenize_global_vars (FILE* obs_file) {
    UT_array* global_vars;
    utarray_new(global_vars, &global_var_symbol_array_icd);

    UT_array* global_var_symbols;
    utarray_new(global_var_symbols, &global_var_symbol_icd);

    StringBuffer* current_token = str_buffer_new(64);
    if (!current_token) {
        return global_vars;
    }

    bool in_str = false;
    bool in_comment = false;
    long int pos;

    int ch;
    while ((ch = fgetc(obs_file)) != EOF) {
        if (in_comment) {
            if (ch == '\n') {
                in_comment = false;
            }
            continue;
        }

        if (in_str) {
            if (ch == '\'') {
                in_str = false;
                char* token_str = str_buffer_duplicate(current_token);
                if (token_str) {
                    GlobalVarSymbol new_symbol = {
                        .kind = GLOBAL_SYMBOL_NAME,
                        .value = { .name = token_str }
                    };
                    utarray_push_back(global_var_symbols, &new_symbol);
                }
                str_buffer_clear(current_token);

                GlobalVarSymbol new_symbol2 = {
                    .kind = GLOBAL_SYMBOL_TOKEN,
                    .value = { .token = TOKEN_OPEN_STR }
                };
                utarray_push_back(global_var_symbols, &new_symbol2);
            } else {
                str_buffer_append_char(current_token, (char)ch);
            }
            continue;
        }

        switch (ch) {
            case '\n':
                if (utarray_len(global_var_symbols) != 0) {
                    utarray_push_back(global_vars, &global_var_symbols);
                }
                utarray_new(global_var_symbols, &global_var_symbol_icd);
                str_buffer_clear(current_token);
                break;
            case '&':
                // Consume any whitespace after '&'
                while ((ch = fgetc(obs_file)) != EOF && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')) {}
                ungetc(ch, obs_file); // Put back the non-whitespace character

                GlobalVarToken* global_var = check_for_global_var(obs_file);
                if (global_var != NULL) {
                    GlobalVarSymbol new_symbol = {
                        .kind = GLOBAL_SYMBOL_TOKEN,
                        .value = { .token = *global_var }
                    };
                    utarray_push_back(global_var_symbols, &new_symbol);
                }
                break;
            case '.':   // type
                Type* type = check_for_type(obs_file);
                if (type != NULL) {
                    GlobalVarSymbol new_symbol = {
                        .kind = GLOBAL_SYMBOL_TYPE,
                        .value = { .type = *type }
                    };
                    utarray_push_back(global_var_symbols, &new_symbol);
                }
                break;
            case '=':
                if (!str_buffer_is_empty(current_token)) {
                    char* token_str = str_buffer_duplicate(current_token);
                    if (token_str) {
                        GlobalVarSymbol new_symbol = {
                            .kind = GLOBAL_SYMBOL_NAME,
                            .value = { .name = token_str }
                        };
                        utarray_push_back(global_var_symbols, &new_symbol);
                    }
                }
                str_buffer_clear(current_token);
                
                GlobalVarSymbol new_symbol2 = {
                    .kind = GLOBAL_SYMBOL_TOKEN,
                    .value = { .token = TOKEN_EQ }
                };
                utarray_push_back(global_var_symbols, &new_symbol2);
                break;
            case '\'':
                in_str = true;
                GlobalVarSymbol new_symbol3 = {
                    .kind = GLOBAL_SYMBOL_TOKEN,
                    .value = { .token = TOKEN_OPEN_STR }
                };
                utarray_push_back(global_var_symbols, &new_symbol3);
                break;
            case '-':
                if (utarray_len(global_var_symbols) != 0) {
                    utarray_push_back(global_vars, &global_var_symbols);
                }
                str_buffer_free(current_token);
                if (check_seek(obs_file, "--")) {
                    return global_vars;
                }
            case ';':
                in_comment = true;
                break;
            default:
                str_buffer_append_char(current_token, (char)ch);
                break;
        }
    }
    
    if (utarray_len(global_var_symbols) != 0) {
        utarray_push_back(global_vars, &global_var_symbols);
    }
    str_buffer_free(current_token);
    return global_vars;
}

TokenStream lexical_analysis(const char* obs_path) {
    TokenStream result = {0};  // Initialize all fields to NULL/0
    
    printf("Attempting to open .obs file...\n");
    FILE* obs_file = fopen(obs_path, "r");
    if (obs_file == NULL) {
        perror("Failed to open .obs file");
        return result;  // Return empty struct
    }
    printf(".obs file opened successfully.\n");

    // Get UT_array of paths
    printf("Tokenizing inclusions...\n");
    result.included_paths = tokenize_inclusions(obs_file);
    if (!result.included_paths) {
        fclose(obs_file);
        return result;  // Return empty struct
    }
    printf("Inclusions tokenized successfully.\n");

    move_fptr_to_section_end(obs_file);

    // Get UT_array of prototype tokens
    printf("Tokenizing prototypes...\n");
    result.prototype_functions = tokenize_prototypes(obs_file);
    if (!result.prototype_functions) {
        fclose(obs_file);
        return result;  // Return empty struct
    }
    printf("Prototypes tokenized successfully.\n");

    move_fptr_to_section_end(obs_file);

    // Get UT_array of global variable tokens
    printf("Tokenizing global variables...\n");
    result.global_vars = tokenize_global_vars(obs_file);
    if (!result.global_vars) {
        fclose(obs_file);
        return result;  // Return empty struct
    }
    printf("Global variables tokenized successfully.\n");

    // Clean up
    fclose(obs_file);
    
    return result;
}