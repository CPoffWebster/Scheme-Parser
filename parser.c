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
typedef struct cell{
    char *symbol;
    struct cell *first;
    struct cell *rest;
};
typedef struct cell Cell;

// STRUCT LIST - for cons
struct list{
    Cell *startList;
};
typedef struct list List;


/****************************************************************
 createCell()
 initializes a new cell
 ****************************************************************/

static Cell *createCell(){
    
    Cell *newCell = (Cell*) malloc(sizeof(Cell*));
    
    if(newCell == NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    newCell->symbol = "";
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
    
    /*printf("test\n");
    
    if(test->rest == NULL){
        printf("WARNING");
    }
    printf("%s", test->symbol);*/
    
    //symbol, first, rest
    
    
    /*if(test->first != NULL){
        printf("test");
        test = test->first;
        printf("%s", test->symbol);
    }
    if(test->rest != NULL){
        printf("POOP");
        test = test->rest;
    }else{
        printf("warning");
        //break;
    }*/
    /*
    if(!strcmp(test->symbol, "")){
        printf("say hello\n");
        if(test->first != NULL){
            //printList(test->first);
            test = test->first;
            printf("test\n");
            
            if(test->first == NULL && test->rest == NULL){
                printf("%s", test->symbol);
            }else{
                printf("NOPE");
            }
        }
    }*/
    Cell* temp;
    temp = createCell();
    
    while(!strcmp(test->symbol, "")){
        if(test->first != NULL && test->rest != NULL){
            printf("(");
        }
        
        if(test->first != NULL){    //first (recursion)
            temp = test->first;
            printList(temp);
        }
        
        if(test->rest != NULL){     //rest (iteration)
            temp = test->rest;
            free(test);
            printList(temp);
            //free(test);
            //test = temp;
        }else{
            printf(")");
            return;
        }
    }
    if(test->first == NULL && test->rest == NULL){
        printf("%s", test->symbol);
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

Cell *s_expr(int depth) {
    
    Cell* local;
    Cell* temp;
    //local = createCell();
    //temp = createCell();
    
    if(!strcmp(token, "(")){
        strcpy(token, getToken());
        //s_expr(depth+1);
        local = createCell();
        local->first = s_expr(depth+1);
        temp = local;
        
        while(strcmp(token, ")")){
            //s_expr(depth+1);
            temp->rest = createCell();
            temp = temp->rest;
            temp->first = s_expr(depth+1);
        }
        temp->rest = NULL;
        if(depth != 0) strcpy(token, getToken());
    }
    else{
        //accounts for #t, #f, /', (), or some word.
        //printString(depth, token);
        local = createCell();
        local->symbol = token;
        //local->first = NULL;
        //local->rest = NULL;
        if(depth != 0) strcpy(token, getToken());
    }
    return local;
}


void S_Expression(){
    
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    int depth = 0;
    
    
    Cell* createList;
    createList = s_expr(depth);
    
    List* buildList;
    buildList = createList;
    
    printList(buildList);
    
    
    
    
}

/*
 Cell* test1;
 Cell* test2;
 
 test1=createCell();
 test2=createCell();
 
 test1->symbol = "";
 test1->first = test2;
 test1->rest = NULL;
 
 test2->symbol = "a";
 test2->first = NULL;
 test2->rest = NULL;
 
 List* test = test1;
 
 printList(test1);*/
