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


/****************************************************************
 INFO
 ****************************************************************/

void S_Expression() {
    int rec;
    /*
    char token[20];
    startTokens(20);
    
    int rec = 0; //initial count of recursive calls
    if(rec == 0){
        //strcpy(token, getToken());
        rec++;
    }if(rec == 1) rec++;
     */
    int temp = rec;
    while(temp != 0){
        printf("\t");
        temp--;
    }
    
    
    
    if (!lookahead)                   //get first char
        c = getchar();
    
    while ((c == ' ') || (c == '\n')) //skip white space
        c = getchar();
    
    if ((c == ')') || (c == '\'')) {  //Case (1): right paren or quote
        rec--;
        lookahead = 0;
        printf("S_Expression\n");
        printf("%c \n", c);
        S_Expression();
    }
    else if (c == '(') {              //Case (2): left paren or ()
        rec++;
        printf("S_Expression\n");
        printf("%c \n", c);
        lookahead = 1;
        c = getchar();
        S_Expression();
        while ((c == ' ') || (c == '\n'))
            c = getchar();
        
    }
    
    /*
     if token is "(" then
        getToken()
        S_exp()
        while (token is not ")"):
            S_exp()
        getToken() usually, but not at 0th recursion
     */
    
    
    else {                            //Case (4): scan for symbol
        lookahead = 1;
        printf("S_Expression\n");
        printf("\t");
        while ((c != '(') && (c != ')') && (c != ' ') && (c != '\n')) {
            printf("%c", c);
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
    /*
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

