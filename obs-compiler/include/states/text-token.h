#ifndef TEXT_TOKEN_H
#define TEXT_TOKEN_H

// Token enum for your language
typedef enum {
    TEXT_TOKEN_EQ,        // =
    TEXT_TOKEN_OPEN_STR,  // '
    TEXT_TOKEN_CALL,      // $
    TEXT_TOKEN_OPEN_FN_PARAM, // (
    TEXT_TOKEN_CLOSE_FN_PARAM, // )
    TEXT_TOKEN_OPEN_FN,       // {
    TEXT_TOKEN_CLOSE_FN,      // }
    TEXT_TOKEN_RET,           // %
} TextToken;

#endif // TOKEN_H