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
#include "lexer.h"



//Token stores the most recent "token" viewed by lexer.c
char *token;


/****************************************************************
printString(int depth, char* token)
 ------------
 c:         The current character in the input stream from the keyboard.
 lookahead: Set to 1 iff the previous call to getToken() required
 looking ahead.
 TAB_LINE:  Set value of a tab line for list indents.
 depth:       Keeps track of how deep the list is.
 ****************************************************************/

void printString(int depth, char* token){
    
    if(!strcmp(token, ")")){
        for(int x=0; x<depth; x++){
            printf("     ");
        }printf("%s\n", token);
    }
    
    else{
        for(int x=0; x<depth; x++){
            printf("     ");
        } printf("S_Expression \n");
        
        if(!strcmp(token, "(")){
            for(int x=0; x<depth; x++){
                printf("     ");
            }
        }else{
            for(int x=0; x<depth+1; x++){
                printf("     ");
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
 ****************************************************************/

void s_expr(int depth) {
    
    if(!strcmp(token, "(")){
        printString(depth, token);
        strcpy(token, getToken());
        s_expr(depth+1);
        while(strcmp(token, ")")){
            s_expr(depth+1);
        }
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    
    else if(!strcmp(token, "()")){
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    else if(!strcmp(token, "#t")){
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    else if(!strcmp(token, "#f")){
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    else if(!strcmp(token, "\'")){
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    else{
        printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    
    
    if (depth == 0){
        printf("\n");
        printf("scheme> ");
    }
    
}


void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    int depth = 0;
    s_expr(depth);
}
