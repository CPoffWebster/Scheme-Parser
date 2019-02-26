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



/****************************************************************
 Data members
 ------------
 c:         The current character in the input stream from the keyboard.
 lookahead: Set to 1 iff the previous call to getToken() required
 looking ahead.
 TAB_LINE:  Set value of a tab line for list indents.
 rec:       Keeps track of how deep the list is.
 ****************************************************************/

static int TAB_LINE = 5;
static int rec;
static _Bool firstTime;
char *token;


/****************************************************************
 S_Expression() implementation notes: The function works by getting
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
// PSEUDO CODE
//    if token is "(" then
//        getToken()
//        S_exp()
//        while (token is not ")"):
//            S_exp()
//        getToken() usually, but not at 0th recursion
//    else
//        deal with "()", "#t", "#f" or a symbol
//        getToken() usually, but not at 0th recursion

void s_expr(int rec) {
    
    /*if (rec == 0){
        printf("\n");
        printf("scheme> ");
    }*/
    //printf("rec: %d\n", rec);
    printf("%*s S_Expression \n", rec*TAB_LINE, "");
    
    if(!strcmp(token, "(")){
        printf("%*s %s \n", rec*TAB_LINE, "", token);
        strcpy(token, getToken());
        firstTime = 1;
        s_expr(rec += 1);
        while(strcmp(token, ")")){
            s_expr(rec -= 1);
            printf("%*s ) \n", rec*TAB_LINE, "");
        }
        if(firstTime != 0) strcpy(token, getToken());
    }
    
    else if(!strcmp(token, "()")){
        printf("%*s %s \n", (rec*TAB_LINE)+TAB_LINE, "", token);
    }
    else if(!strcmp(token, "#t")){
        printf("%*s %s \n", (rec*TAB_LINE)+TAB_LINE, "", token);
    }
    else if(!strcmp(token, "#f")){
        printf("%*s %s \n", (rec*TAB_LINE)+TAB_LINE, "", token);
    }
    else if(!strcmp(token, "\'")){
        printf("%*s %s \n", (rec*TAB_LINE)+TAB_LINE, "", token);
    }
    else{
        printf("%*s %s \n", (rec*TAB_LINE)+TAB_LINE, "", token);
    }
    
    if(firstTime != 0) strcpy(token, getToken());
    /*
    if(strcmp(token, ")")){
        s_expr(rec);
    }*/
    
}


void S_Expression(){
    token = (char *) calloc(20, sizeof(char));
    startTokens(20);
    strcpy(token, getToken());
    firstTime = 0;
    rec = 0;
    s_expr(rec);
}
