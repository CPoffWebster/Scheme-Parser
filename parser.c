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
 printList()
 given a pointer to such a cons-cell structure,
 will print out the list in parenthesized form.
 
 
 ****************************************************************/

void printList(){
    
    
}


/****************************************************************
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
    
}

void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    int depth = 0;
    s_expr(depth);
}
