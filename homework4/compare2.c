#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

int compare(TYPE left, TYPE right)
{
   struct student* dataLeft = (struct student*)left;
   struct student* dataRight = (struct student*)right;

   return strcmp(dataLeft->name, dataRight->name);
}

void print_type(TYPE curval)
{
   char **val = (char **)curval;
   printf("%s",**val);
}