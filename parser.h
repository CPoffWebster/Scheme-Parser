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

// Environment for the defined functions, created in eval()
List environment;

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
void S_Expression(int firstTime);


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


/****************************************************************
 Function: eval
 --------------------
 This method evaluates a given list in scheme.
 
 */
List eval(List list, List environment);


/****************************************************************
 BUILT IN SCHEME FUNCTIONS
 ****************************************************************/

/****************************************************************
 Function: quoteFn
 --------------------
 Parses list as a single element
 
 */
List quoteFn(List list);

/****************************************************************
 Function: carFn
 --------------------
 Returns the first element of a list
 
 */
List carFn(List list);

/****************************************************************
 Function: cdrFn
 --------------------
 Returns the rest element of a list
 
 */
List cdrFn(List list);

// only list->rest
List cdrNull(List list);

/****************************************************************
 Function: symbolFn
 --------------------
 Returns #t if element is a symbol, else #f
 
 */
List symbolFn(List list);

/****************************************************************
 Function: consFn
 --------------------
 Constructs a list given two or more elements
 
 */
List consFn(List list1, List list2);


/****************************************************************
 Function: nullFn
 --------------------
 returns #t cell if the list is null, otherwise returns () or #f cell
 
 */
List nullFn(List list);

/****************************************************************
 Function: nullFnTF
 --------------------
 nullFn except turns true/false values, this function is used in
 the appendFn
 
 */
int nullFnTF(List list);

/****************************************************************
 Function: appendFn
 --------------------
 appends two lists together
 This takes two arguments and returns a list that appends the second
 list to the end of the first.
 For example(append '(a b c) '(d e f))
 returns the list (a b c d e f).
 
 */
List appendFn(List list1, List list2);

// HELPER METHOD
// nullFn except turns true/false values
int nullFnTF(List list);

/****************************************************************
 Function: equalFn
 --------------------
 Returns #t if its arguments evaluate to the same value and #f otherwise
 This function evaluates if a list is a single symbol to account for the
 first example and calls equalListFn to evaluate a list (with not other
 list inside) is equal to another list.
 ex. (equal? 'a 'b) returns #t
 ex. (equal? '(a (c) b) '(a (d) b))) returns #f
 
 */
List equalFn(List list1, List list2);

// HELPER METHODS
// evaluates if the list is a single symbol
int symbolFnTF(List list);
// evaluates if a list is equal to a list (NO lists inside of lists found)
int equalListFn(List list1, List list2);

/****************************************************************
 Function: assocFn
 --------------------
 returns the pair associated with the symbol, and #f if the symbol
 is not the first element of any pair. For example,
 (assoc 'joan '((john smith) (joan doe) (marcia law)))  returns (joan doe)
 (assoc 'john '((john smith) (joan doe) (marcia law)))  returns (john smith)
 (assoc 'jean '((john smith) (joan doe) (marcia law)))  returns #f
 
 */
List assocFn(List symbol, List list);

/****************************************************************
 Function: condFn
 --------------------
 Used for flow of control in defining Scheme functions
 
 */
List condFn(List list, List environment);


/****************************************************************
 Function: listFn
 --------------------
 returns cons of a list with #f

 */
List listFn(List list, List environment);

/****************************************************************
 Function: subtractFn
 --------------------
 (- a b) will return a-b by converting both into ints, making the
 subtraction calculation, and then returning the solved value as
 createCell(calculation). This function supports tower-of-hanoi
 
 */
List subtractFn(List list1, List list2);


/****************************************************************
 DEFINING USER-DEFINED FUNCTIONS
 ****************************************************************/

/****************************************************************
 Function: defineFn
 --------------------
 Adds the defined symbol or defined function to the environment
 
 */
List defineFn(List list);
List defineSymbol(List symbol, List list);

// HELPER METHOD
// used for seeing if list is a user defined function/symbol
int assocFnTF(List symbolList, List list);

/****************************************************************
 Function: userDefFn
 --------------------
 After a function has been created, userDefFn() calls and runs the
 function after assigning parameters. userDefFn updates the env
 recursively.
 
 */

List userDefFn(List list, List environment);

// HELPER METHODS
// assign parameters to given variables, return updated environment
List assignParameters(List argument, List parameter, List environment);
List assignMultParameters(List argument, List parameter, List environment);


#endif
