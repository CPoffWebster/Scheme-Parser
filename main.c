//
//  main.c
//  Part1
//
//  Created by Charlie Poff-Webster on 2/19/19.
//  Copyright © 2019 Charlie Poff-Webster. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"


int main(){

    printf("A parser for a subset of Scheme. \n");
    printf("Type any Scheme expression and its \n");
    printf("'parse tree' will be printed out. \n");
    printf("Type Ctrl-c to quit.: \n \n");
    
    printf("scheme> ");
    
    while(SIGQUIT){
        S_Expression();
    }
    
    return 0;
}
