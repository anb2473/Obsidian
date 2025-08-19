#define _CONSOLE
#undef _WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include "../../include/utils/utarray.h"
#include "../../include/structs/token-stream.h"
#include "../../include/lexer.h"
#include "../../include/states/prototype-symbol.h"
#include "../../include/states/global-var-symbol.h"
#include "../../include/states/text-symbol.h"
#include "../../include/consts/type-map.h"
#include "../../include/structs/fn-decl.h"

void print_included_paths(UT_array* paths) {
    if (paths == NULL) {
        printf("No included paths found.\n");
        return;
    }

    printf("Included Paths:\n");
    char** p = NULL;
    while ((p = (char**)utarray_next(paths, p))) {
        printf("  %s\n", *p);
    }
}

void print_prototype_functions(UT_array* functions) {
    if (functions == NULL) {
        printf("No prototype functions found.\n");
        return;
    }

    printf("Prototype Functions:\n");
    UT_array** p = NULL;
    while ((p = (UT_array**)utarray_next(functions, p))) {
        printf("  ");
        PrototypeSymbol* q = NULL;
        while ((q = (PrototypeSymbol*)utarray_next(*p, q))) {
            switch (q->kind) {
                case SYMBOL_NAME:
                    printf("%s ", q->value.name);
                    break;
                case SYMBOL_TYPE:
                    printf(".%s ", type_map[q->value.type].name);
                    break;
                case SYMBOL_TOKEN:
                    switch (q->value.token) {
                        case TOKEN_OPEN_BRACE:
                            printf("( ");
                            break;
                        case TOKEN_CLOSE_BRACE:
                            printf(") ");
                            break;
                        case TOKEN_RET:
                            printf("-> ");
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_global_vars(UT_array* vars) {
    if (vars == NULL) {
        printf("No global variables found.\n");
        return;
    }

    printf("Global Variables:\n");
    UT_array** p = NULL;
    while ((p = (UT_array**)utarray_next(vars, p))) {
        printf("  ");
        GlobalVarSymbol* q = NULL;
        while ((q = (GlobalVarSymbol*)utarray_next(*p, q))) {
            switch (q->kind) {
                case GLOBAL_SYMBOL_NAME:
                    printf("%s ", q->value.name);
                    break;
                case GLOBAL_SYMBOL_TYPE:
                    printf(".%s ", type_map[q->value.type].name);
                    break;
                case GLOBAL_SYMBOL_TOKEN:
                    switch (q->value.token) {
                        case TOKEN_EQ:
                            printf("= ");
                            break;
                        case TOKEN_OPEN_STR:
                            printf("'");
                            break;
                        case TOKEN_CONST:
                            printf("&rod ");
                            break;
                        case TOKEN_MUTABLE:
                            printf("&mut ");
                            break;
                        case TOKEN_BSS:
                            printf("&bss ");
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
    }
    printf("\n");
}

void print_text_section(UT_array* text_section) {
    if (text_section == NULL) {
        printf("No text section found.\n");
        return;
    }

    printf("Text Section:\n");
    FnDecl* p = NULL;
    while ((p = (FnDecl*)utarray_next(text_section, p))) {
        UT_array* fn_lines = p->fn_lines;
        UT_array** q = NULL;
        while ((q = (UT_array**)utarray_next(fn_lines, q))) {
            printf("  ");
            TextSymbol* r = NULL;
            while ((r = (TextSymbol*)utarray_next(*q, r))) {
                switch (r->kind) {
                    case TEXT_SYMBOL_REG:
                        printf("%s ", r->value.reg);
                        break;
                    case TEXT_SYMBOL_TYPE:
                        printf(".%s ", type_map[r->value.type].name);
                        break;
                    case TEXT_SYMBOL_DATA:
                        printf("&%s ", r->value.data);
                        break;
                    case TEXT_SYMBOL_FN:
                        printf("%s", r->value.fn);
                    case TEXT_SYMBOL_TOKEN:
                        switch (r->value.token) {
                            case TEXT_TOKEN_EQ:
                                printf("= ");
                                break;
                            case TEXT_TOKEN_CALL:
                                printf("$ ");
                                break;
                            case TEXT_TOKEN_OPEN_STR:
                                printf("'");
                                break;
                            case TEXT_TOKEN_OPEN_FN_PARAM:
                                printf("(");
                                break;
                            case TEXT_TOKEN_CLOSE_FN_PARAM:
                                printf(")");
                                break;
                            case TEXT_TOKEN_OPEN_FN:
                                printf("{");
                                break;
                            case TEXT_TOKEN_CLOSE_FN:
                                printf("}");
                                break;
                            case TEXT_TOKEN_RET:
                                printf("return ");
                                break;
                        }   
                        break;
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char* file_path = argv[1];
    TokenStream token_stream = lexical_analysis(file_path);

    print_included_paths(token_stream.included_paths);
    print_prototype_functions(token_stream.prototype_functions);
    print_global_vars(token_stream.global_vars);
    print_text_section(token_stream.text_section);

    // Free memory
    utarray_free(token_stream.included_paths);
    utarray_free(token_stream.prototype_functions);
    utarray_free(token_stream.global_vars);
    utarray_free(token_stream.text_section);

    return 0;
}