/****************************************************************
 File: parser.h
 
 Charlie Poff-Webster
 ****************************************************************/


#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include "lexer.h"


/****************************************************************
 Data Structure: List
 --------------------
 List is a data structure that holds cells. Cells are created using
 a symbol, a first element, and a rest element. Symbol simply holds
 the token inside the cell, while first and rest are linked to other
 cells within the list.
 
 */

 struct cell{
     char *symbol;
     struct cell *first;
     struct cell *rest;
 }; typedef struct cell *List;


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
 Prints the parse tree.
 
 */
void printString(int depth, char* token);


/****************************************************************
 Function: printList
 --------------------
 Prints the list of cells accounting for both cons cell and
 symbol cells.
 
 */
void printList(List list, int depth);


#endif
