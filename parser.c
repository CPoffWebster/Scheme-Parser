/****************************************************************
 File: parser.c
 
 Charlie Poff-Webster
 
 -------------
 This file implements the interface given in parser.c.
 ****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
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

static char c;
static int lookahead;
static int TAB_LINE = 5;
static int rec = 0;


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

void S_Expression() {
    if (rec == 0){          //BUGS INPUT ENTIRELY INSIDE A LIST
        printf("\n");
        printf("scheme> ");
    }
    
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
            c = getchar();
        }//while
        printf("\n");
    }
}




