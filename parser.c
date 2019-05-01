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

List eval(List list, List environment){
    List temp = list;
    List temp2 = list;
    
    if(carFn(list) != NULL){
        if(carFn(list)->symbol != NULL){
            char* symbol = carFn(list)->symbol;         //create symbol char
            
            if(!strcmp(symbol, "exit")){
                printf("Have a nice day!\n");
                exit(0);
            }
            
            // adds function to environment
            if(!strcmp(symbol, "define")){
                if(!symbolFnTF(carFn(cdrFn(list)))){    // defining a function
                    return defineFn(list);
                }
                else{                                   // else defining a symbol
                    return defineSymbol(carFn(cdrFn(list)), carFn(cdrFn(cdrFn(list))));
                }
            }

            // these must be called before eval() in temp
            if(!strcmp(symbol, "cond")){
                return condFn(cdrFn(list), environment);
            }
            if(!strcmp(symbol, "quote")){
                return quoteFn(carFn(cdrFn(list)));
            }
            
            // Scheme Functions
            if (cdrFn(list) != NULL && carFn(cdrFn(list)) != NULL) {    // so that temp can be created
                temp = eval(carFn(cdrFn(list)), environment);           // List of 2nd conCell List
            }
            if(cdrFn(list) != NULL && cdrFn(cdrFn(list)) != NULL && carFn(cdrFn(cdrFn(list))) != NULL){
                temp2 = eval(carFn(cdrFn(cdrFn(list))), environment);   // one cdr deeper than temp (defined above)
            }
                // evaluate different scheme functions
                if(!strcmp(symbol, "environment")){
                    return environment;
                }
                if(!strcmp(symbol, "-")){
                    return subtractFn(temp, temp2);
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
                    return consFn(temp, temp2);
                }
                if(!strcmp(symbol, "list")){
                    return listFn(cdrFn(list));//listFn(eval(cdrFn(list), environment));
                }
                if(!strcmp(symbol, "null?")){
                    return nullFn(temp);
                }
                if(!strcmp(symbol, "append")){
                    return appendFn(temp, temp2);
                }
                if(!strcmp(symbol, "equal?")){
                    return equalFn(temp, temp2);
                }
                if(!strcmp(symbol, "assoc")){
                    return assocFn(temp, temp2);
                }
        }
    }
    // find symbols from the environment -- if so print out the value
    if(carFn(assocFn(list, environment)) != NULL){
        List defVal = carFn(cdrFn(assocFn(list, environment)));
        if(assocFnTF(list, environment)){   // Symbol
            //printf("symbol refered\n");
            return defVal;
        }
    }else if(carFn(list) != NULL && carFn(assocFn(carFn(list), environment)) != NULL){
        //printf("function refered\n");
        return userDefFn(list, environment);
    }
    return list;
}

/****************************************************************
 DEFINING USER-DEFINED FUNCTIONS
 ****************************************************************/

// evaluates a function
List userDefFn(List list, List environment){
    List function = assocFn(carFn(list), environment);
    List parameter = cdrFn(carFn(cdrFn(carFn(cdrFn(function)))));
    if(cdrNull(parameter) == NULL){
        List argument = eval(carFn(cdrFn(list)), environment);
        environment = assignParameters(argument, parameter, environment);    // single parameter
    }
    else{
        List argument = cdrFn(list);
        environment = assignMultParameters(argument, parameter, environment); // multiple parameters
    }
    List functionCall = carFn(cdrFn(cdrFn(carFn(cdrFn(function)))));
    return eval(functionCall, environment);
}

// assigns single-variable parameters
List assignParameters(List argument, List parameter, List environment){
    List tempArgument = consFn(argument, createCell(NULL));
    List tempList = consFn(carFn(parameter), tempArgument);
    return environment = consFn(tempList, environment);
}

// assigns multi-variable parameters
List assignMultParameters(List argument, List parameter, List environment){
    List tempArgument = consFn(eval(carFn(argument), environment), createCell(NULL));
    List tempList = consFn(carFn(parameter), tempArgument);
    environment = consFn(tempList, environment);
        if(cdrNull(parameter) != NULL){
            return assignMultParameters(cdrFn(argument), cdrFn(parameter), environment);
        }
        return environment;
    return environment;
}

/****************************************************************
 ADDING SYMBOLS+FUNCTIONS TO ENVIRONMENT
 ****************************************************************/

// Adds the defined symbol to the environment
List defineSymbol(List symbol, List list){
    //printf("symbol in environment\n");
    List evalList = eval(list, environment);
    List tempList = consFn(evalList, createCell(NULL));
    List tempDefine = consFn(symbol, tempList);
    environment = consFn(tempDefine, environment);
    return symbol;
}

// Adds a function to the environment
List defineFn(List list){
    //printf("function in environment\n");
    List symbol = carFn(carFn(cdrFn(list)));
    List tempList = consFn(list, createCell(NULL));
    List tempDefine = consFn(symbol, tempList);
    environment = consFn(tempDefine, environment);
    return symbol;
}

/****************************************************************
 BUILT IN SCHEME FUNCTIONS
 ****************************************************************/

// Parses list as a single element
List quoteFn(List list){
    return list;
}

// returns the first element of a list
List carFn(List list){
    return list->first;
}

// Returns the rest element of a list
List cdrFn(List list){
    if(list->rest == NULL){
        if(strcmp(list->symbol, "#f")){
           return createCell("#f");
        }
    }
    return list->rest;
}

// ex: (cdrNull '(a)) -> NULL
List cdrNull(List list){
    return list->rest;
}

// Returns #t if element is a symbol, else #f
List symbolFn(List list){
    //if it is a list (more than one element) than return false
    if(list->symbol != NULL && carFn(list) == NULL && strcmp(list->symbol, "#f")){
        return createCell("#t");
    }
    else return createCell("()");
}

// returns cons of a list with #f
//List listFn(List list){
//    return consFn(list, createCell("#f"));
//}

List listFn(List list){
    printf("listFn called\n");
    //list = eval(list, environment);
    printf("list: ");
    printList(list, 1);
    printf("\n");
    if(!strcmp(nullFn(list)->symbol, "#t")){
        return eval(list, environment);
    }
    printf("env: ");
    printList(environment, 1);
    printf("\nCARFNlist: ");
    printList(eval(carFn(list), environment), 1);
    printf("\n");
    return consFn(eval(carFn(list), environment), listFn(cdrFn(list)));
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
    return consFn(carFn(list1), appendFn(cdrNull(list1), list2));
}

//helper function for appendFn
int nullFnTF(List list){
    if(list == NULL) return 1;
    if(!strcmp(list->symbol, "#f") || !strcmp(list->symbol, "()")){
        return 1;
    }else return 0;
}

// returns #t for null lists, otherwise () or #f
List nullFn(List list){
    if(list == NULL){
        return createCell("#t");
    }
    if(list->symbol != NULL){
        if(!strcmp(list->symbol, "#f") || !strcmp(list->symbol, "()")){
            return createCell("#t");
        }
        if(!strcmp(list->symbol, "") && carFn(list) == NULL){   // for user-defined symbols
            return createCell("#t");
        }
    }
    return createCell("#f");
}

// returns #t if the lists are the same, otherwise () or #f
List equalFn(List list1, List list2){
    // is the list a single symbol
    if(!symbolFnTF(list1) && !symbolFnTF(list2)){
        // call the car and cdr of the list
        if(equalListFn(carFn(list1), carFn(list2)) && equalListFn(cdrFn(list1), cdrFn(list2))){
            return createCell("#t");
        }
    }else{
        // call just the symbol
        if(equalListFn(list1, list2)){
            return createCell("#t");
        }
    }
    return createCell("()");
}

// private fn called by equalFn: evaluates equal? of a list
int equalListFn(List list1, List list2){
    // if it is not a list.. make it one
    if(!symbolFnTF(list1) && !symbolFnTF(list2)){
        return equalListFn(carFn(list1), carFn(list2)) && equalListFn(cdrFn(list1), cdrFn(list2));
    }
    // evaluates a single symbol
    if(list1 == NULL && list2 == NULL) return 1; // if nothing (shouldn't be called)
    if(carFn(list1) == NULL){                   // if the list is length 1
        if(carFn(list2) == NULL){
            if(!strcmp(list1->symbol, list2->symbol)){
                return 1; // the symbol is equal
            }else return 0;
        }else return 0;
    }
    // evaluate a list
    if(!strcmp(carFn(list1)->symbol, carFn(list2)->symbol)){
        // recursion
        if(cdrFn(list1) == NULL){
            if(cdrFn(list2) == NULL){
                return equalListFn(carFn(list1), carFn(list2)); // recursive call of car
            }else return 0;
        }else return equalListFn(cdrFn(list1), cdrFn(list2));   // recursive call of cdr
    }else return 0;
    return 1;
}

// Returns #t if element is a symbol, else #f
int symbolFnTF(List list){
    //if it is a list (more than one element) than return false
    if(list->symbol != NULL && cdrNull(list) == NULL){
        return 1;
    }
    else return 0;
}

//returns the pair associated with the symbol, else #f
List assocFn(List symbolList, List list){
    //if list is comparing to one elmt
    if(carFn(list) == NULL){
        if(!strcmp(symbolList->symbol, list->symbol)) return list;
        else return createCell("()");
    }// if first element is equal to the symbol
    if(!strcmp(symbolList->symbol, carFn(carFn(list))->symbol)) return carFn(list);
    else{
        if(cdrFn(list) != NULL) return assocFn(symbolList, cdrFn(list)); // if more elements, check them
        else return createCell("()");       // if no more elements, return false
    }
}

//returns true if the symbol is in the list, else false
int assocFnTF(List symbolList, List list){
    //if list is comparing to one elmt
    if(carFn(list) == NULL){
        if(!strcmp(symbolList->symbol, list->symbol)) return 1;
        else return 0;
    }// if first element is equal to the symbol
    if(!strcmp(symbolList->symbol, carFn(carFn(list))->symbol)) return 1;
    else{
        if(cdrFn(list) != NULL) return assocFnTF(symbolList, cdrFn(list)); // if more elements, check them
        else return 0;       // if no more elements, return false
    }
}

// if condition one is true, else look at next condition, and so on
List condFn(List list, List environment){
    List temp;
    int trueFunction;   // if or else
    if(carFn(carFn(list)) != NULL){     // evaluates function
        temp = carFn(carFn(list));
        trueFunction = 0;
    }
    else{                               // evaluates #t or else function
        temp = carFn(list);
        trueFunction = 1;
    }
    // if statement is true
    if(!strcmp(eval(temp, environment)->symbol, "#t") || !strcmp(eval(temp, environment)->symbol, "else")){
        if(!trueFunction){
            return eval(carFn(cdrFn(carFn(list))), environment);
        }
        if(trueFunction){
            return eval(carFn(cdrFn(list)), environment);
        }
    }
    else{   // recurssion
        return condFn(cdrFn(list), environment);
    }
    printf("returning list - ERROR\n");
    return list; // to remove error
}

// Subtracts the 2nd input from the first
List subtractFn(List list1, List list2){
    //convert to integer
    char* first = list1->symbol;
    char* rest = list2->symbol;
    int number1 = atoi(first);
    int number2 = atoi(rest);
    //subtract
    int subtract = number1 - number2;
    //convert back to char*
    char newValue[20];
    sprintf(newValue, "%i", subtract);
    return createCell(newValue);
}

void S_Expression(int firstTime){
    if(firstTime){                              // initiate environment
        environment = createCell(NULL);
    }
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    
    List buildList = s_expr(0);                 // depth starts at 0
    printList(eval(buildList, environment), 1); // depth starts at 1
    printf("\n");
}
