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
 Initializes a new cell.
 createCell() initializes both cons-cells and symbol-cells.
 When createCell() is called it is called as either (NULL) or with
 a (token). (NULL) initializes the symbol cell, while (token)
 initializes the symbol-cell. Both first and rest are initialized
 as NULL. This is final for symbol-cells, but will be updated as
 needed for cons-cells within s_expr().
 ****************************************************************/

List createCell(char* symbol){
    
    List newCell = (List) malloc(sizeof(struct cell));
    if(newCell == NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    
    if(symbol == NULL){             // symbol not given (cons cell)
        newCell->symbol = "";
    }else{                          // symbol given (symbol cell)
        newCell->symbol = malloc(sizeof(char)*strlen(symbol) + 1);
        strcpy(newCell->symbol, symbol);
    }
    newCell->first = NULL;          // initializes cell as a symbol cell
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
 Given a pointer to a cons-cell structure, printList() will print
 out the list in parenthesized form by analyzing if the cell is a
 symbol cell or a cons cell. If the cell is a cons cell than
 printList() will make recursive calls for both first and rest.
 ****************************************************************/

void printList(List list, int startBool){
    
    if(list != NULL){
        if(strcmp(list->symbol, "")){       // symbol cell
            printf("%s", list->symbol);
        }else{                              // cons cell
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
 Given a collection of scheme syntax, s_expr() will creates a List
 of cells that are built with both a symbol, first, and rest. This
 method is the process of building the List given the scheme input.
 The program has a process of creating both symbol-cells and cons-
 cells by using the helper method createCell(). This program supports
 token "()" -> "#f" and "\'" -> "quote". s_expr() uses recursion
 to complete this entire process.
 
 ****************************************************************/

List s_expr(int depth) {
    
    List local, temp;
    
    if(!strcmp(token, "(")){                // given s_expr from class
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
        if(depth != 0) strcpy(token, getToken());
    }
    else if(!strcmp(token, "()")){          // returns () as #f
        local = createCell("#f");
        if(depth != 0) strcpy(token, getToken());
    }
    else if(!strcmp(token, "\'")){          // returns '(a) as (quote (a))

        local = createCell(NULL);
        local->first = createCell("quote");
        strcpy(token, getToken());
        local->rest = createCell(NULL);
        temp = local->rest;
        temp->first = s_expr(depth);
    }
    else{                                   // creates symbol cell with token
        local = createCell(token);
        if(depth != 0) strcpy(token, getToken());
    }
    
    return local;
}


void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    
    List buildList = s_expr(0);     // depth starts at 0
    printList(buildList, 1);        // startBool starts as True
}
