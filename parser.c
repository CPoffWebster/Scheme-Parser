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


/****************************************************************
 eval(List list)
 This method evaluates a given list in scheme. This functional
 evaluates the internal representation of the list and can perform
 functions by calling methods: quote, car, cdr, symbol? and cons
 
 ****************************************************************/
List temp, temp2, temp3;

List eval(List list){
    if(carFn(list) != NULL){
        if(carFn(list)->symbol != NULL){
            
            char* symbol = carFn(list)->symbol;         //create symbol char
            
            if(!strcmp(symbol, "exit")){
                printf("Have a nice day!\n");
                exit(0);
            }
            
            if (cdrFn(list) != NULL && carFn(cdrFn(list)) != NULL) {    // so that temp can be created
                temp = eval(carFn(cdrFn(list)));            // List of 2nd conCell List
            }
                if(!strcmp(symbol, "quote")){
                    return quoteFn(carFn(cdrFn(list)));     // no eval() recursion
                }
                if(!strcmp(symbol, "car")){
                    return carFn(temp);
                }
                if(!strcmp(symbol, "cdr")){
                    return cdrFn(temp);
                }
                if(!strcmp(symbol, "symbol?")){
                    return symbolFn(temp);
                }
                if(!strcmp(symbol, "cons")){
                    // the second list is one cdr deeper than temp (defined above)
                    return consFn(temp, eval(carFn(cdrFn(cdrFn(list)))));
                }
            
            if(!strcmp(symbol, "null?")){
                return nullFn(temp);
            }
            if(!strcmp(symbol, "append")){
                return appendFn(temp, eval(carFn(cdrFn(cdrFn(list)))));
            }
            
            
        }
    }
    return list;
}

// Parses list as a single element
List quoteFn(List list){
    if(list->symbol != NULL && !strcmp(list->symbol, "()")){
        return NULL;
    }
    return list;
}
// returns the first element of a list
List carFn(List list){
    return list->first;
}
// Returns the rest element of a list
List cdrFn(List list){
    return list->rest;
}
// Returns #t if element is a symbol, else #f
List symbolFn(List list){
    //if it is a list (more than one element) than return false
    if(list->symbol != NULL && cdrFn(list) == NULL){
        return createCell("#t");
    }
    else return createCell("()");
}
// Constructs a list given two or more elements
List consFn(List list1, List list2){
    List consCell = createCell(NULL);

    // check to see if List1 has #f
    if(symbolFn(list1) != NULL && !strcmp(list1->symbol, "#f")){
        // check if both lists are #f
        if(symbolFn(list2) != NULL && !strcmp(list2->symbol, "#f")){
            return createCell("(())");
        }
        consCell->first = list2;
        return consCell;
    }
    // check to see if List2 has #f
    if(symbolFn(list1) != NULL && !strcmp(list2->symbol, "#f")){
        consCell->first = list1;
        return consCell;
    }
    consCell->first = list1;
    consCell->rest = list2;
    
    return consCell;
}

//appends the second list to the end of the first
List appendFn(List list1, List list2){
    if(nullFnTF(list1)) return list2;
    return consFn(carFn(list1), appendFn(cdrFn(list1), list2));
}

//helper function for appendFn
int nullFnTF(List list){
    if(list == NULL) return 1;
    if(!strcmp(list->symbol, "#f")){
        return 1;
    }else return 0;
}

// returns #t for null lists, otherwise () or #f
List nullFn(List list){
    if(list == NULL) return createCell("#t");
    if(!strcmp(list->symbol, "#f")){
        return createCell("#t");
    }else return createCell("()");
}

/*equal?. This has two arguments, both s-expressions, and it returns #t if its arguments evaluate to the same value (in the case of lists, the structure returned must be identical) and #f otherwise. This is trickier than it may sound, because it requires a simultaneous navigation of both s-expressions. Recursion is a must! For example,
(equal? '(a b) '(a b)) returns #t
(equal? '(a b) '(a (a b))) returns #f   */
List equalFn(List list1, List list2){
    return 0;
}

/*assoc. This has two arguments, the first of which is a symbol, the second a so-called "association list" (to be explained in class). It returns the pair associated with the symbol, and #f if the symbol is not the first element of any pair. For example,
(assoc 'joan '((john smith) (joan doe) (marcia law)))  returns (joan doe)
(assoc 'john '((john smith) (joan doe) (marcia law)))  returns (john smith)
(assoc 'jean '((john smith) (joan doe) (marcia law)))  returns #f   */
List assocFn(char symbol, List list){
    return 0;
}

//cond. The multiple-alternative conditional.
//cond is, as you know, used for flow of control in defining Scheme functions, so it is extremely important that it works properly. (If you want to add the if construct as well, please do.)
List condFn(){
    return 0;
}




void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    
    List buildList = s_expr(0);     // depth starts at 0
    //printList(buildList, 1);        // startBool starts as True
    printList( eval(buildList), 1);
    printf("\n");
}
