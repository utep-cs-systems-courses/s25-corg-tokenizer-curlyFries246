#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"
#define MAX 100  

int main() {
    puts("Welcome");

    List *hist = init_history();
    char c[MAX];  
    char **pt = NULL;  
    char option;  

    while (1) {
        fputs("Enter an option to continue\n'q' to quit\n't' to type a phrase and use tokenizer\n'h' for history\n> ", stdout);
        fflush(stdout);

        option = getchar();  
        while (getchar() != '\n');  

        if (option == EOF) {
            goto done;
        }

        switch (option) {
            case 'q':
                puts("You selected quit. Thank you.");
                goto done;
            
            case 't':
                printf("Enter a string: \n");
                fgets(c, MAX, stdin);  
                c[strcspn(c, "\n")] = 0;  

                printf("\nThe string has been tokenized:\n");
                pt = tokenizer(c);  
                print_tokens(pt);  
                add_history(hist, c);  
                break;
            
            case 'h':
                printf("Log of phrases: \n");
                print_history(hist);
                break;  

            default:
                printf("Unrecognized option '%c', please try again!\n", option);
        }
    }

done:
    if (pt) {
        free_tokens(pt);  
    }
    free_history(hist);
    return 0;
}

