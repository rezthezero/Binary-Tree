/*
 * tree.h
 *
 *  Created on: 23-Nov-2020
 *      Author: Rishabh
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The number of nodes the tree can hold
#define MAX_SIZE 100

// The pointer to a node in the tree
typedef struct node *tree_pointer;

// The defining of the tree
typedef struct node {
	int data;
	tree_pointer lchild, rchild;
};

// Defining a stack for iterative post order traversal
typedef struct Stack {
	tree_pointer data[MAX_SIZE];
	int top;
} Stack;

// Defining a queue for level order traversal
typedef struct{
	tree_pointer data[MAX_SIZE];
	int front;
	int rear;
}Queue;

/* Function for initiating a queue
 * setting the front and rear variables to 0
 */
void initq(Queue *q);

/* A function that returns 1 if queue is empty
 * or 0 if it is not empty
 */
int queueFull(Queue *q);

/* A function that returns 1 if queue is full
 * or 0 if it is not full
 */
int queueEmpty(Queue *q);

/*A function to add an element to the queue*/
void addQ(Queue *q,tree_pointer item);

/* A function to delete an element from the queue*/
tree_pointer deleteQueue(Queue *q);

/*Function to initiate a stack setting top to -1*/
void initS(Stack *s);

/* Function that returns 1 if stack is empty
 * or returns 0 if it is not
 */
int isEmptyS(Stack *s);

/* A function that returns 1 if stack is full
 * or returns 0 if it is not
 */
int isFullS(Stack *s);

/* A function to push an element to the stack */
void pushS(Stack *s, tree_pointer item);

/* A function that removes and returns the
 * topmost element of the stack
 */
tree_pointer popS(Stack *s);

/* Function for recursive inorder traversal */
void inOrder(tree_pointer ptr);

/* Function for recursive preorder traversal */
void preOrder(tree_pointer ptr);

/* Function for recursive postorder traversal */
void postOrder(tree_pointer ptr);

/* Function for iterative level order traversal */
void levelOrder(tree_pointer ptr);

/* Recursive function to insert an element into the tree */
void insert(tree_pointer *root, int data);

/* Iterative function to insert an element into the tree */
void insert_iter(tree_pointer *root, int data);

/* Function to search the tree for a defined element */
int search(tree_pointer root, int key);


/* Iterative function for inorder traversal */
void inOrder_iter(tree_pointer root);

/* Iterative function for preorder traversal */
void preOrder_iter(tree_pointer root);

/* Iterative function for postorder traversal */
void postOrder_iter(tree_pointer root);

/* Searching function made to be used in creating trees from
 * inorder and preorder / inorder and postorder
 * Searches for an element found in pre or postorder
 * and returns its index in inorder
 */
int find(int arr[], int instart, int inend, int key);

// Function for using inorder and preorder to generate a tree
tree_pointer preToTree(int preorder[], int inorder[], int instart, int inend);

// Function for using inorder and postorder to generate a tree
tree_pointer postToTree(int postorder[], int inorder[], int instart, int inend);

#endif /* TREE_H_ */
