#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

// Returns true if there is a tab, space, or newline
int space_char(char c) {
    return (c == '\t' || c == ' ' || c == '\n');
}

// Returns true if the character is NOT a space/tab/newline
int non_space_char(char c) {
    return (c != '\t' && c != ' ' && c != '\0' && c != '\n');
}

// Finds the start of the next token
char *token_start(char *str) {
    while (space_char(*str)) {
        str++;
    }
    return (*str == '\0') ? NULL : str; 
}

// Finds the first space/tab/newline after a token
char *token_terminator(char *token) {
    while (non_space_char(*token)) {
        token++;
    }
    return token;
}

// Counts the number of tokens in the string
int count_tokens(char *str) {
    int num = 0;
    while (*str != '\0') {
        str = token_start(str);
        if (str == NULL) break;
        num++;
        str = token_terminator(str);
    }
    return num;
}

// Copies a substring of length `len` from `inStr`
char *copy_str(char *inStr, short len) {
    char *copyStr = (char*) malloc(len + 1);
    char *pt = copyStr;
    while (len > 0) {
        *copyStr = *inStr;
        inStr++;
        copyStr++;
        len--;
    }
    *copyStr = '\0'; 
    return pt;
}

// Tokenizes the string into an array of strings
char **tokenizer(char *str) {
    int num = count_tokens(str);
    char **pt = (char **) malloc((num + 1) * sizeof(char *));
    char **spt = pt;

    while ((str = token_start(str))) {
        char *temp = token_terminator(str);
        int len = temp - str;
        *pt = copy_str(str, len);
        pt++;
        str = temp;
    }
    *pt = NULL; 
    return spt;
}

// Prints each token
void print_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("%s\n", tokens[i]);
    }
}

// Frees memory allocated for tokens
void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
