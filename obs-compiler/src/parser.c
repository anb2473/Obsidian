#include <stdio.h>
#include <stdbool.h>
#include "../include/utils/utarray.h"

// Include icds
#include "../include/icds/char-ptr-icd.h"

// Include limits
#include <limits.h>  // for PATH_MAX
#ifndef PATH_MAX
#define PATH_MAX 4096   // fallback max path length
#endif

bool check_seek(FILE* obs_file, char* target_str) {
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

UT_array* parse_inclusions(FILE* obs_file) {
    UT_array* path_array = NULL;
    utarray_new(path_array, &char_ptr_icd);

    char current_path[PATH_MAX];
    size_t idx = 0;

    int ch;
    while ((ch = fgetc(obs_file)) != EOF) {
        if (ch == '-') {
            long pos = ftell(obs_file);
            if (check_seek(obs_file, "---")) {
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

int parse (char* obs_path) {
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

    UT_array* included_paths = parse_inclusions(obs_file);
}