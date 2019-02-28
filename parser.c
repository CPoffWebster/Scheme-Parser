/****************************************************************
 File: parser.c
 
 Charlie Poff-Webster
 
 -------------
 This file implements the interface given in parser.c.
 ****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"



//Token stores the most recent "token" viewed by lexer.c
char *token;


/****************************************************************
printString(int depth, char* token)
 ------------
Private helper method to print the given token at the correct depth.
The method takes the depth, which keeps track of how many lists
 inside of lists the string is, and token, which is the given
 token that will be printed.
 ****************************************************************/

void printString(int depth, char* token){
    
    // Prints ")" with no "S_Expression"
    if(!strcmp(token, ")")){
        for(int x=0; x<depth; x++){
            printf("     ");            // tab line
        }printf("%s\n", token);
    }
    
    // Prints S_Expression with either "(" or the given token
    else{
        for(int x=0; x<depth; x++){
            printf("     ");            // tab line
        } printf("S_Expression \n");
        
        if(!strcmp(token, "(")){
            for(int x=0; x<depth; x++){
                printf("     ");        // tab line
            }
        }else{
            for(int x=0; x<depth+1; x++){
                printf("     ");        // tab line
            }
        }
        printf("%s\n", token);
    }
}


/****************************************************************
 s_expr(int depth)
 implementation notes: The function works by getting
 the first character, in case the previous call required lookahead,
 then skipping over whitespace. The main part is the "if" statement
 that handles 4 cases:
 (1) Leading char is ")" or "'" return, no lookahead
 (2) Leading char is "(" scan to find ")",
 if ")" found, no lookahead, return "()",
 if not found, lookahead=true
 (3) #: lookahead for t or f, lookahead=false,
 if found, return "#t" or "#f", else abort
 (4) Look for other collections of characters,
 scan for entire symbol up to ( or ()
 
 s_expr(int depth)
 s_expr ultimately prints the input string seperated into different
 tokens and listed by what list the token is inside (depth). This
 will look similar to a parse tree.
 s_expres() is a simple recursive method that looks for "(" & ")"
 and then different characters: #t, #f, /', (), or some word.

 ****************************************************************/

void s_expr(int depth) {
    
    if(!strcmp(token, "(")){
        printString(depth, token);
        strcpy(token, getToken());
        s_expr(depth+1);
        
        while(strcmp(token, ")")) s_expr(depth+1);
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    else{
        //accounts for #t, #f, /', (), or some word.
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    
    //prints scheme after each parse tree is printed
    if (depth == 0) printf("\nscheme> ");
    
}

void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    int depth = 0;
    s_expr(depth);
}
