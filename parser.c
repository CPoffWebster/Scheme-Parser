/****************************************************************
 File: parser.c
 
 Charlie Poff-Webster
 
 -------------
 This file implements the interface given in parser.h.
 ****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"


/****************************************************************
 Data members
 ------------
 lexeme:    "String" variable that contains the token.
 c:         The current character in the input stream from the keyboard.
 lookahead: Set to 1 iff the previous call to getToken() required
 looking ahead.
 ****************************************************************/
//static char *lexeme;
//static char c;
//static int lookahead;


/****************************************************************
INFO
 ****************************************************************/
/*
void startTokens (int maxLength)
{
    lookahead = 0;
    lexeme = NULL;
    newToken(maxLength);
}//startTokens
*/



static char *lexeme;
static char c;
static int lookahead;
static int TAB_LINE = 5;
int rec = 0;


/****************************************************************
 INFO
 ****************************************************************/

void S_Expression() {
    
    
    if (!lookahead)                   //get first char
        c = getchar();
    
    while ((c == ' ') || (c == '\n')) //skip white space
        c = getchar();
    
    if ((c == ')') || (c == '\'')) {  //Case (1): right paren or quote
        rec--;
        lookahead = 0;
        printf("%*s %c \n", rec*TAB_LINE, "", c);
        S_Expression();
    }
    
    else if (c == '(') {              //Case (2): left paren or ()
        printf("%*s S_Expression\n", rec*TAB_LINE, "");
        printf("%*s %c", rec*TAB_LINE, "", c);
        rec++;
        lookahead = 1;
        c = getchar();
        if (c == ')'){
            printf("%c \n", c);
            c = getchar();
            rec--;
        } else{
            printf("\n");
        }
        S_Expression();
        //while ((c == ' ') || (c == '\n'))       //THIS LINE MIGHT BE EXTRANIOUS PLEASE CHECK ME ASAP
          //  c = getchar();
    }
    
    else if (c == '#') {              //Case (3): #t or #f
        lookahead = 0;
        c = getchar();
        if ((c != 't') && (c != 'f')) {
            printf("Illegal symbol after #.\n");
            exit(1);
        }
        printf("%*s S_Expression\n", rec*TAB_LINE, "");
        printf("%*s#", (rec*TAB_LINE)+TAB_LINE, "");
        printf("%c \n", c);
        S_Expression();
    }

    else {                            //Case (4): scan for symbol
        lookahead = 1;
        printf("%*s S_Expression\n", rec*TAB_LINE, "");
        printf("%*s", (rec*TAB_LINE)+TAB_LINE, "");
        while ((c != '(') && (c != ')') && (c != ' ') && (c != '\n')) {
            printf("%c", c);
            //printf("%*s %c \n", rec*TAB_LINE, "", c);
            c = getchar();
        }//while
        printf("\n");
    }
    

    
    
    
    /*
     {
     if token is "(" then
        getToken()
        S_exp()
        while (token is not ")"):
            S_exp()
        getToken() usually, but not at 0th recursion
     else
        deal with "()", "#t", "#f" or a symbol
        getToken() usually, but not at 0th recursion
     }
}
    
    else if (c == '#') {              //Case (3): #t or #f
        lookahead = 0;
        c = getchar();
        if ((c != 't') && (c != 'f')) {
            printf("Illegal symbol after #.\n");
            exit(1);
        }
        if (c == 't')
            strcpy(lexeme, "#t");
        else
            strcpy(lexeme, "#f");
    }
    
    return lexeme;
     */
}

