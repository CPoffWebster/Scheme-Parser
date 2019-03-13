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


// STRUCT CELL
struct cell{
    char *symbol;
    struct cell *first;
    struct cell *rest;
};
typedef struct cell Cell;

// STRUCT LIST - for cons
struct list{
    Cell *consCell;
};
typedef struct list List;


/****************************************************************
 createCell()
 initializes a new cell
 ****************************************************************/

static Cell *createCell(char* token){
    
    Cell *newCell = (Cell*) malloc(sizeof(Cell*));
    
    if(newCell == NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    newCell->symbol = token;
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

void printList(Cell* test){
    Cell* temp;
    Cell* temp2;
    char* printme;
    
    if(test->first == NULL && test->rest == NULL){
        printme = test->symbol;
        printf("%s", printme);
    }
    
    temp = test->first;
    printList(temp);
    
    temp2 = test->rest;
    printList(temp2);
    
}


/****************************************************************
 s_expr(int depth)
 s_expr ultimately prints the input string seperated into different
 tokens and listed by what list the token is inside (depth). This
 will look similar to a parse tree.
 s_expres() is a simple recursive method that looks for "(" & ")"
 and then different characters: #t, #f, /', (), or some word.

 ****************************************************************/

Cell *s_expr(int depth) {
    
    Cell* local;
    Cell* temp;
    local = createCell(token);
    temp = createCell(token);
    
    if(!strcmp(token, "(")){
        strcpy(token, getToken());
        //s_expr(depth+1);
        local->first = s_expr(depth+1);
        temp = local;
        
        while(strcmp(token, ")")){
            //s_expr(depth+1);
            temp->rest = createCell(token);
            temp = temp->rest;
            temp->first = s_expr(depth+1);
        }
        temp->rest = NULL;
        strcpy(token, getToken());
        //if(depth != 0) temp->rest = NULL; //strcpy(token, getToken());
    }
    else{
        //accounts for #t, #f, /', (), or some word.
        //printString(depth, token);
        if(depth != 0) strcpy(token, getToken());
    }
    return local;
}

// allocate nodes local and temp
/*
if (token == '(') {
    getNextToken();
    local->first = S_expr();    // recursion!
    temp = local;
    while (token != ")")
    {
        temp->rest = allocate a new node
        temp = temp->rest;
        temp->first = S_expr();   // recursion!
    }
    temp->rest = NULL;  // the end of the list, make sure it's null terminated
}
else
{
    // deal with symbols, #t, #f, etc...
}*/

void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    int depth = 0;
    Cell* printme;
    printme = s_expr(depth);
    //List* print;
    //print->consCell = s_expr(depth);
    printList(printme);
    
}

