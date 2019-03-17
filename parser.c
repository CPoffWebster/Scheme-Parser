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
 createCell()
 Initializes a new cell
 This cell is created as a symbol-cell with both first/rest NULL,
 but is updated to be a cons-cell if needed within the program.
 ****************************************************************/

List createCell(char* symbol){
    
    List newCell = (List) malloc(sizeof(struct cell));
    if(newCell == NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    
    if(symbol == NULL){     //symbol not given
        newCell->symbol = "";
    }else{                  //symbol given
        newCell->symbol = malloc(sizeof(char)*strlen(symbol) + 1);
        strcpy(newCell->symbol, symbol);
    }
    newCell->first = NULL;
    newCell->rest = NULL;
    return newCell;
}

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

void printList(List list, int startBool){
    
    if(list != NULL){
        if(strcmp(list->symbol, "")){   // symbol cell
            printf("%s", list->symbol);
        }else{                          // cons cell
            if(startBool) printf("(");
            
            if(list->first != NULL){        // first (recursion)
                printList(list->first, 1);
            }
            
            if(list->rest != NULL){         // rest (recursion)
                printf(" ");
                printList(list->rest, 0);
            }else{
                printf(")");
            }
        }
    }
}


/****************************************************************
 s_expr(int depth)
 s_expr ultimately prints the input string seperated into different
 tokens and listed by what list the token is inside (depth). This
 will look similar to a parse tree.
 s_expres() is a simple recursive method that looks for "(" & ")"
 and then different characters: #t, #f, /', (), or some word.
 
 ****************************************************************/

List s_expr(int depth) {
    
    List local, temp;
    
    if(!strcmp(token, "(")){
        strcpy(token, getToken());
        local = createCell(NULL);
        local->first = s_expr(depth+1);
        temp = local;
        
        while(strcmp(token, ")")){
            temp->rest = createCell(NULL);
            temp = temp->rest;
            temp->first = s_expr(depth+1);
        }
        temp->rest = NULL;
    }
    else if(!strcmp(token, "()")){
        local = createCell("#f");
    }
    else{
        local = createCell(token);
    }
    
    if(depth != 0) strcpy(token, getToken());
    return local;
}


void S_Expression(){
    
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    int depth = 0;
    
    List buildList = s_expr(depth);
    printList(buildList, 1);
}
