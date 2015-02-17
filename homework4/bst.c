/*
 * Zach and Kyle 2/17/2015
 * VIM 
 * Project for CS261
 *
File: bst.c
Implementation of the binary search tree data structure.

*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"


struct Node {
   TYPE         val;
   struct Node *left;
   struct Node *right;
};

struct BSTree {
   struct Node *root;
   int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
   function to initialize the binary search tree.
   param tree
pre: tree is not null
post:		tree cnt is 0
tree root is null
*/

void initBSTree(struct BSTree *tree)
{
   assert(tree != 0);
   tree->root = malloc(sizeof(struct Node*));
   tree->root = 0;
   tree->cnt = 0;
}

/*
   function to create a binary search tree.
param: none
pre: none
post: 	
tree != 0	
tree->count = 0
tree->root = 0;
*/

struct BSTree*  newBSTree()
{
   struct BSTree* tree = malloc(sizeof(struct BSTree*));
   initBSTree(tree);	 
   return tree;
}

/*----------------------------------------------------------------------------*/
/*
   function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
pre: none
post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
   if(node->left != 0)
      _freeBST(node->left);
   if(node->right != 0)
      _freeBST(node->right);
   free(node);
}

/*
   function to clear the nodes of a binary search tree
param: tree    a binary search tree
pre: tree ! = null
post: the nodes of the tree are deallocated
tree->root = 0;
tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
   assert(tree != 0);
   _freeBST(tree->root);
   tree->root = 0;
   tree->cnt = 0;
}

/*
   function to deallocate a dynamically allocated binary search tree
param: tree   the binary search tree
pre: tree != null;
post: all nodes and the tree structure itself are deallocated.
*/
void deleteBSTree(struct BSTree *tree)
{
   assert(tree != 0);
   _freeBST(tree->root);
   free(tree);
}

/*----------------------------------------------------------------------------*/
/*
   function to determine if  a binary search tree is empty.

param: tree    the binary search tree
pre:  tree is not null
post: 1 = it's empty 0 = it's not empty
*/
int isEmptyBSTree(struct BSTree *tree) { 
   assert(tree != 0);
   if(tree->root == 0)
      return 1;
   else
      return 0;
}


/*
   function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { 
   assert(tree != 0);
   return tree->cnt;
}



/*----------------------------------------------------------------------------*/
/*
   recursive helper function to add a node to the binary search tree.
HINT: You have to use the compare() function to compare values.
param:  cur	the current root node
val	the value to be added to the binary search tree
pre:	val is not null
*/
struct Node *_addNode(struct Node *cur, TYPE val)
{
   assert(val != 0);
   if(cur == 0){
      struct Node* newNode = malloc(sizeof(struct Node*));
      newNode->val = val;
      newNode->right = 0;
      newNode->left = 0;
      return newNode;
   }
   if(compare(val, cur->val) == 0 || compare(val, cur->val) == 1)
      cur->right = _addNode(cur->right, val);   
   if(compare(val, cur->val) == -1)
      cur->left = _addNode(cur->left, val);
   return cur;
}

/*
   function to add a value to the binary search tree
param: tree   the binary search tree
val		the value to be added to the tree

pre:	tree is not null
val is not null

pose:  tree size increased by 1
tree now contains the value, val
*/
void addBSTree(struct BSTree *tree, TYPE val)
{
   tree->root = _addNode(tree->root, val);
   tree->cnt++;
}


/*
   function to determine if the binary search tree contains a particular element
HINT: You have to use the compare() function to compare values.
param:	tree	the binary search tree
val		the value to search for in the tree
pre:	tree is not null
val is not null
post:	none
*/

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
   assert(tree != 0);
   assert(val != 0);
   struct Node* temp = tree->root;
   while(temp != 0){
      if(compare(val, temp->val) == 0)
	 return 1;
      else if(compare(val, temp->val) == 1)
	 temp = temp->right;
      else if(compare(val, temp->val) == -1)
	 temp = temp->left;
   }
   return 0;
}

/*
   helper function to find the left most child of a node
   return the value of the left most child of cur
param: cur		the current node
pre:	cur is not null
post: none
*/

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
   assert(cur != 0);
   struct Node* temp = cur;
   while(temp->left != 0)
      temp = temp->left;
   return temp->val;
}


/*
   recursive helper function to remove the left most child of a node
HINT: this function returns cur if its left child is NOT NULL. Otherwise,
it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

param: cur	the current node
pre:	cur is not null
post:	the left most node of cur is not in the tree
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
   assert(cur != 0);
   struct Node* temp = cur->right;
   if(cur->left != 0){
      cur->left = _removeLeftMost(cur->left);
      return cur;
   }
   else{
      free(cur);
      cur = 0;
      return temp;
   }
} 


/*
   recursive helper function to remove a node from the tree
HINT: You have to use the compare() function to compare values.
param:	cur	the current node
val	the value to be removed from the tree
pre:	val is in the tree
cur is not null
val is not null
*/
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
   assert(cur != 0);
   assert(val != 0);
   if(compare(val, cur->val) == 0){
      if(cur->right != 0){
	 cur->val = _leftMost(cur->right);
	 cur->right = _removeLeftMost(cur->right);
      }
      else{
	 struct Node* temp = cur;
	 cur = cur->left;
	 free(temp);
      }
   }   
   else if(compare(val, cur->val) == -1){
      cur->left = _removeNode(cur->left, val);
   }
   else if(compare(val, cur->val) == 1){
      cur->right = _removeNode(cur->right, val);
   }
   return cur;
}


/*
   function to remove a value from the binary search tree
param: tree   the binary search tree
val		the value to be removed from the tree
pre:	tree is not null
val is not null
val is in the tree

pose:	tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, TYPE val)
{
   tree->root = _removeNode(tree->root, val);
   tree->cnt--;
}



/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used 
   in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
   if (cur == 0) return;
   printf("(");
   printNode(cur->left);	 
   /*Call print_type which prints the value of the TYPE*/
   print_type(cur->val);
   printNode(cur->right);
   printf(")");
}

void printTree(struct BSTree *tree) {
   if (tree == 0) return;	 
   printNode(tree->root);	 
}
/*----------------------------------------------------------------------------*/

#endif


/************************************************************************************************************************
  from here to the end of this file are a set of fucntions for testing the fucntions of the BST
 ***************************************************************************************************************************/
/*
   function to built a Binary Search Tree (BST) by adding numbers in this specific order
   the graph is empty to start: 50, 13, 110 , 10

*/
struct BSTree *buildBSTTree() {
   /*     50
	  13  110
	  10 
	  */
   struct BSTree *tree	= newBSTree();		

   /*Create value of the type of data that you want to store*/
   struct data *myData1 = (struct data *) malloc(sizeof(struct data));
   struct data *myData2 = (struct data *) malloc(sizeof(struct data));
   struct data *myData3 = (struct data *) malloc(sizeof(struct data));
   struct data *myData4 = (struct data *) malloc(sizeof(struct data));
   struct data *myData5 = (struct data *) malloc(sizeof(struct data));
   struct data *myData6 = (struct data *) malloc(sizeof(struct data));

   myData1->number = 50;
   myData1->name = "rooty";
   myData2->number = 13;
   myData2->name = "lefty";
   myData3->number = 110;
   myData3->name = "righty";
   myData4->number = 10;
   myData4->name = "lefty of lefty";
   myData5->number = 15;
   myData5->name = "right of lefty";
   myData6->number = 14;
   myData6->name = "left of right of lefty";

   /*add the values to BST*/
   addBSTree(tree, myData1);
   addBSTree(tree, myData2);
   addBSTree(tree, myData3);
   addBSTree(tree, myData4);
   addBSTree(tree, myData5);
   addBSTree(tree, myData6);

   return tree;
}

/*
   function to print the result of a test function
param: predicate:  the result of the test 
nameTestFunction : the name of the function that has been tested
message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message){
   if (predicate)
      printf("%s(): PASS %s\n",nameTestFunction, message);
   else
      printf("%s(): FAIL %s\n",nameTestFunction, message);        
}

/*
   fucntion to test each node of the BST and their children

*/
void testAddNode() {
   struct BSTree *tree	= newBSTree();

   struct data myData1,  myData2,  myData3,   myData4;

   myData1.number = 50;
   myData1.name = "rooty";
   addBSTree(tree, &myData1);
   //check the root node
   if (compare(tree->root->val,&myData1) != 0) {
      printf("addNode() test: FAIL to insert 50 as root\n");
      return;
   }
   //check the tree->cnt value after adding a node to the tree
   else if (tree->cnt != 1) {
      printf("addNode() test: FAIL to increase count when inserting 50 as root\n");
      return;
   }
   else printf("addNode() test: PASS when adding 50 as root\n");
   printTree(tree);
   printf("\n");

   myData2.number = 13;
   myData2.name = "lefty";
   addBSTree(tree, &myData2);

   //check the position of the second element that is added to the BST tree
   if (compare(tree->root->left->val,  &myData2) != 0) {
      printf("addNode() test: FAIL to insert 13 as left child of root\n");
      return;
   }
   else if (tree->cnt != 2) {
      printf("addNode() test: FAIL to increase count when inserting 13 as left of root\n");
      return;
   }
   else printf("addNode() test: PASS when adding 13 as left of root\n");
   printTree(tree);
   printf("\n");

   myData3.number = 110;
   myData3.name = "righty";
   addBSTree(tree, &myData3);

   //check the position of the third element that is added to the BST tree    
   if (compare(tree->root->right->val,  &myData3) != 0) {
      printf("addNode() test: FAIL to insert 110 as right child of root\n");
      return;
   }
   else if (tree->cnt != 3) {
      printf("addNode() test: FAIL to increase count when inserting 110 as right of root\n");
      return;
   }
   else printf("addNode() test: PASS when adding 110 as right of root\n");
   printTree(tree);
   printf("\n");

   myData4.number = 10;
   myData4.name = "righty of lefty";
   addBSTree(tree, &myData4);

   //check the position of the fourth element that is added to the BST tree
   if (compare(tree->root->left->left->val,  &myData4) != 0) {
      printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
      return;
   }
   else if (tree->cnt != 4) {
      printf("addNode() test: FAIL to increase count when inserting 10 as left of left of root\n");
      return;
   }
   else printf("addNode() test: PASS when adding 10 as left of left of root\n");
   printTree(tree);
   printf("\n");
}

/*
   fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree() {
   struct BSTree *tree = buildBSTTree();

   struct data myData1,  myData2,  myData3,  myData4, myData5;

   myData1.number = 50;
   myData1.name = "rooty";
   myData2.number = 13;
   myData2.name = "lefty";
   myData3.number = 110;
   myData3.name = "righty";
   myData4.number = 10;
   myData4.name = "lefty of lefty";
   myData5.number = 111;
   myData5.name = "not in tree";

   printTestResult(containsBSTree(tree, &myData1), "containsBSTree", "when test containing 50 as root");

   printTestResult(containsBSTree(tree, &myData2), "containsBSTree", "when test containing 13 as left of root");

   printTestResult(containsBSTree(tree, &myData3), "containsBSTree", "when test containing 110 as right of root");

   printTestResult(containsBSTree(tree, &myData4), "containsBSTree", "when test containing 10 as left of left of root");

   //check containsBSTree fucntion when the tree does not contain a node    
   printTestResult(!containsBSTree(tree, &myData5), "containsBSTree", "when test containing 111, which is not in the tree");

}

/*
   fucntion to test the left_Most_element 

*/
void testLeftMost() {
   struct BSTree *tree = buildBSTTree();

   struct data myData3, myData4;

   myData3.number = 110;
   myData3.name = "righty";
   myData4.number = 10;
   myData4.name = "lefty of lefty";

   printTestResult(compare(_leftMost(tree->root), &myData4) == 0, "_leftMost", "left most of root");

   printTestResult(compare(_leftMost(tree->root->left), &myData4) == 0, "_leftMost", "left most of left of root");

   printTestResult(compare(_leftMost(tree->root->left->left), &myData4) == 0, "_leftMost", "left most of left of left of root");

   printTestResult(compare(_leftMost(tree->root->right), &myData3) == 0, "_leftMost", "left most of right of root");

}

void testRemoveLeftMost() {
   struct BSTree *tree = buildBSTTree();
   struct Node *cur;

   cur = _removeLeftMost(tree->root);

   printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");

   cur = _removeLeftMost(tree->root->right);
   printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");

   cur = _removeLeftMost(tree->root);
   printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
}

void testRemoveNode() {
   struct BSTree *tree = buildBSTTree();
   struct Node *cur;
   struct data myData1,  myData2,  myData3,  myData4, myData5, myData6;

   myData1.number = 50;
   myData1.name = "rooty";
   myData2.number = 13;
   myData2.name = "lefty";
   myData3.number = 110;
   myData3.name = "righty";
   myData4.number = 10;
   myData4.name = "lefty of lefty";
   myData5.number = 15;
   myData5.name = "right of lefty";
   myData6.number = 14;
   myData6.name = "left of right of lefty";

   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myData2);
   printTestResult(compare(tree->root->val, &myData1) == 0 && compare(tree->root->left->val, &myData6) == 0, "_removeNode", "remove 13");
   printTree(tree);
   printf("\n");
   
   _removeNode(tree->root, &myData5);
   printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->right == NULL, "_removeNode", "remove 15");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myData3);
   printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "_removeNode", "remove 110");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myData6);
   printTestResult(compare(tree->root->val, &myData1) == 0 && compare(tree->root->left->val, &myData4) == 0, "_removeNode", "remove 14");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myData4);
   printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove 10");
   printTree(tree);
   printf("\n");

   cur = _removeNode(tree->root, &myData1);
   printTestResult(cur == NULL, "_removeNode", "remove 50");      
   printTree(tree);
   printf("\n");
}

/*
 * The following are test cases for the student struct
 */

struct BSTree *buildBSTTree_2(){
   struct BSTree *tree = newBSTree();

   struct student *myStud1 = malloc(sizeof(struct student*));
   struct student *myStud2 = malloc(sizeof(struct student*));
   struct student *myStud3 = malloc(sizeof(struct student*));
   struct student *myStud4 = malloc(sizeof(struct student*));
   struct student *myStud5 = malloc(sizeof(struct student*));
   struct student *myStud6 = malloc(sizeof(struct student*));

   myStud1->name = "Kyle";
   myStud1->id = 1;
   myStud2->name = "Chris";
   myStud2->id = 2;
   myStud3->name = "Zachary";
   myStud3->id = 3;
   myStud4->name = "Abby";
   myStud4->id = 4;
   myStud5->name = "Greg";
   myStud5->id = 5;
   myStud6->name = "Daniel";
   myStud6->id = 6;

   addBSTree(tree, myStud1);
   addBSTree(tree, myStud2);
   addBSTree(tree, myStud3);
   addBSTree(tree, myStud4);
   addBSTree(tree, myStud5);
   addBSTree(tree, myStud6);

   return tree;
}

void testAddNode_2() {
   struct BSTree *tree	= newBSTree();

   struct student myStud1,  myStud2,  myStud3,   myStud4;

   myStud1.name = "Kyle";
   myStud1.id = 1;
   addBSTree(tree, &myStud1);
   //check the root node
   if (compare(tree->root->val,&myStud1) != 0) {
      printf("addNode() test: FAIL to insert Kyle as root\n");
      return;
   }
   //check the tree->cnt value after adding a node to the tree
   else if (tree->cnt != 1) {
      printf("addNode() test: FAIL to increase count when inserting Kyle as root\n");
      return;
   }
   else printf("addNode() test: PASS when adding Kyle as root\n");
   printTree(tree);
   printf("\n");


   myStud2.name = "Chris";
   myStud2.id = 2;
   addBSTree(tree, &myStud2);

   //check the position of the second element that is added to the BST tree
   if (compare(tree->root->left->val,  &myStud2) != 0) {
      printf("addNode() test: FAIL to insert Chris as left child of root\n");
      return;
   }
   else if (tree->cnt != 2) {
      printf("addNode() test: FAIL to increase count when inserting Chris as left of root\n");
      return;
   }
   else printf("addNode() test: PASS when adding Chris as left of root\n");
   printTree(tree);
   printf("\n");

   myStud3.name = "Zachary";
   myStud3.id = 3;
   addBSTree(tree, &myStud3);

   //check the position of the third element that is added to the BST tree    
   if (compare(tree->root->right->val,  &myStud3) != 0) {
      printf("addNode() test: FAIL to insert Zachary as right child of root\n");
      return;
   }
   else if (tree->cnt != 3) {
      printf("addNode() test: FAIL to increase count when inserting Zachary as right of root\n");
      return;
   }
   else printf("addNode() test: PASS when adding Zachary as right of root\n");
   printTree(tree);
   printf("\n");

   myStud4.name = "Abby";
   myStud4.id = 4;
   addBSTree(tree, &myStud4);

   //check the position of the fourth element that is added to the BST tree
   if (compare(tree->root->left->left->val,  &myStud4) != 0) {
      printf("addNode() test: FAIL to insert Abby as left child of left of root\n");
      return;
   }
   else if (tree->cnt != 4) {
      printf("addNode() test: FAIL to increase count when inserting Abby as left of left of root\n");
      return;
   }
   else printf("addNode() test: PASS when adding Abby as left of left of root\n");
   printTree(tree);
   printf("\n");
}
/*
   fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree_2() {
   struct BSTree *tree = buildBSTTree_2();

   struct student myStud1,  myStud2,  myStud3,  myStud4, myStud5;

   myStud1.name = "Kyle";
   myStud1.id = 1;
   myStud2.name = "Chris";
   myStud2.id = 2;
   myStud3.name = "Zachary";
   myStud3.id = 3;
   myStud4.name = "Abby";
   myStud4.id = 4;
   myStud5.name = "Zeke";
   myStud5.id = 5;

   printTestResult(containsBSTree(tree, &myStud1), "containsBSTree", "when test containing Kyle as root");

   printTestResult(containsBSTree(tree, &myStud2), "containsBSTree", "when test containing Chris as left of root");

   printTestResult(containsBSTree(tree, &myStud3), "containsBSTree", "when test containing Zachary as right of root");

   printTestResult(containsBSTree(tree, &myStud4), "containsBSTree", "when test containing Abby as left of left of root");

   //check containsBSTree fucntion when the tree does not contain a node    
   printTestResult(!containsBSTree(tree, &myStud5), "containsBSTree", "when test containing Zeke, which is not in the tree");

}
/*
   fucntion to test the left_Most_element 

*/
void testLeftMost_2() {
   struct BSTree *tree = buildBSTTree_2();

   struct student myStud3, myStud4;

   myStud3.name = "Zachary";
   myStud3.id = 3;
   myStud4.name = "Abby";
   myStud4.id = 4;

   printTestResult(compare(_leftMost(tree->root), &myStud4) == 0, "_leftMost", "left most of root");

   printTestResult(compare(_leftMost(tree->root->left), &myStud4) == 0, "_leftMost", "left most of left of root");

   printTestResult(compare(_leftMost(tree->root->left->left), &myStud4) == 0, "_leftMost", "left most of left of left of root");

   printTestResult(compare(_leftMost(tree->root->right), &myStud3) == 0, "_leftMost", "left most of right of root");

}

void testRemoveLeftMost_2() {
   struct BSTree *tree = buildBSTTree_2();
   struct Node *cur;

   cur = _removeLeftMost(tree->root);

   printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");

   cur = _removeLeftMost(tree->root->right);
   printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");

   cur = _removeLeftMost(tree->root);
   printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
}

void testRemoveNode_2() {
   struct BSTree *tree = buildBSTTree_2();
   struct Node *cur;
   struct student myStud1,  myStud2,  myStud3,  myStud4, myStud5, myStud6;

   myStud1.name = "Kyle";
   myStud1.id = 1;
   myStud2.name = "Chris";
   myStud2.id = 2;
   myStud3.name = "Zachary";
   myStud3.id = 3;
   myStud4.name = "Abby";
   myStud4.id = 4;
   myStud5.name = "Greg";
   myStud5.id = 5;
   myStud6.name = "Daniel";
   myStud6.id = 6;
   
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myStud2);
   printTestResult(compare(tree->root->val, &myStud1) == 0 && compare(tree->root->left->val, &myStud6) == 0, "_removeNode", "remove Chris");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myStud5);
   printTestResult(compare(tree->root->val, &myStud1) == 0 && tree->root->left->right == NULL, "_removeNode", "remove Greg");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myStud3);
   printTestResult(compare(tree->root->val, &myStud1) == 0 && tree->root->right == NULL, "_removeNode", "remove Zachary");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myStud6);
   printTestResult(compare(tree->root->val, &myStud1) == 0 && compare(tree->root->left->val, &myStud4) == 0, "_removeNode", "remove Daniel");
   printTree(tree);
   printf("\n");

   _removeNode(tree->root, &myStud4);
   printTestResult(compare(tree->root->val, &myStud1) == 0 && tree->root->left == 0, "_removeNode", "remove Abby");
   printTree(tree);
   printf("\n");

   cur = _removeNode(tree->root, &myStud1);
   printTestResult(cur == NULL, "_removeNode", "remove Kyle");       
   printTree(tree);
   printf("\n");
}

/*


   Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){	


   //After implementing your code, please uncommnet the following calls to the test functions and test your code 
   if(1){
   testAddNode();

   printf("\n");
   testContainsBSTree();

   printf("\n");
   testLeftMost();

   printf("\n");
   testRemoveLeftMost();

   printf("\n");
   testRemoveNode();

   printf("\n");
   }
   if(0){
   testAddNode_2();

   printf("\n");
   testContainsBSTree_2();

   printf("\n");
   testLeftMost_2();

   printf("\n");
   testRemoveLeftMost_2();

   printf("\n");
   testRemoveNode_2();

   printf("\n");
   }
   return 0;



}
