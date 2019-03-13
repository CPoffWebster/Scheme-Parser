/****************************************************************
 File: parser.h
 
 Charlie Poff-Webster
 ****************************************************************/


#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include "lexer.h"

/****************************************************************
 Function: S_Expression()
 --------------------
 S_Expression is a recursive function that prints an input list.
 It will print lists inside of lists (with an extra tab line for
 each list). In this way the user can see the "parse tree" that
 the list of lists creates. This parse tree, as well as the fact
 that this function is recursive, is what seperates S_Expression
 from the previously built getToken() as tested by lextester.c.
 
*/
void S_Expression();


/****************************************************************
 Function: printString
 --------------------
 prints the parse tree
 
 */
void printString(int depth, char* token);


/****************************************************************
 Function: printList
 --------------------
 Prints a list of cons cells
 
 */
void printList();


#endif
