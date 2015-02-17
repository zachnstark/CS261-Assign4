#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

int compare(TYPE left, TYPE right)
{
   struct student* dataLeft = (struct student*)left;
   struct student* dataRight = (struct student*)right;

   if(strcmp(dataLeft->name, dataRight->name) == 0){
      return 0;
   }

   else if(strcmp(dataLeft->name, dataRight->name) < 0){
      return -1;
   }

   else
      return 1;
}

void print_type(TYPE curval)
{
   char **val = (char **)curval;
   printf("%s",*val);
}
