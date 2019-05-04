
/****************************************************************
main.c
 Created by Charlie Poff-Webster on 2/19/19.
 Copyright © 2019 Charlie Poff-Webster. All rights reserved.
 
 Runs working scheme code within C.
 This program has built in C functions and then also has the
 capability to create user defined functions and symbols. The
 program works using a List cell structure which can be found
 in parser.h. The userdefined functions and symbols are created
 within the environment which is updated whenever a user (defines)
 something new. This environment works recursively with a local
 environment when working with running user defined functions.
 
 Most of the code can be found in parser.c with the documentation
 found in parser.h. lexer.h and lexer.c was provided.
 
 To run the program simply compile using the makefile and run with
 "./scheme" to exit simply press ctrl-c or execute (exit)
 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

List environment;

int main(){
    
    printf("A parser for a subset of Scheme. \n");
    printf("Type any Scheme expression and it \n");
    printf("will parse it, includes user def functions. \n");
    printf("Type Ctrl-c or (exit) to quit.: \n");
    printf("\nscheme> ");
    int firstTime = 1;
    
    while(1){
        S_Expression(firstTime);
        firstTime = 0;
        printf("\nscheme> ");
    }
    
    return 0;
}
