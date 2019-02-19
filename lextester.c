#include <stdlib.h>
#include <string.h>
#include "lexer.h"

main()
{
 char token[20];

 startTokens(20);

 printf("Enter any number of lines of input.\n");
 printf("This will echo tokens as they are found.\n");
 printf("Terminate by typing \"@@\" (two @\'s in a row).\n");

 strcpy(token, getToken());

 while (strcmp(token, "@@"))
   {
     printf("%s\n", token);
     strcpy(token, getToken());
   }

}
