/*
 * tree.c
 *
 *  Created on: 11-Nov-2020
 *      Author: Rishabh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct node *tree_pointer;

typedef struct node {
	int data;
	tree_pointer lchild, rchild;
};

typedef struct{
	tree_pointer data[MAX_SIZE];
	int front;
	int rear;
}Queue;

void initq(Queue *q){
	q->front=0;
	q->rear=0;
}

int queueFull(Queue *q){
	return q->rear==MAX_SIZE-1;
}

void addQ(Queue *q,tree_pointer item){
	if(queueFull(q)){
		fprintf(stderr,"\n QUEUE IS FULL \n");fflush(stderr);
	}
	else{
		q->data[++q->rear]=item;
	}
}

int queueEmpty(Queue *q){
	return q->front==q->rear;
}

tree_pointer deleteQueue(Queue *q){
	if(queueEmpty(q)){
		fprintf(stderr,"\n QUEUE IS EMPTY \n");fflush(stdout);
		return NULL;
	}
	else{
		return q->data[++q->front];
	}
}

typedef struct Stack {
	tree_pointer data[MAX_SIZE];
	int top;
} Stack;

void initS(Stack *s) {
	s->top = -1;
}

int isEmptyS(Stack *s) {
	return s->top == -1;
}

int isFullS(Stack *s) {
	return s->top == MAX_SIZE;
}

void pushS(Stack *s, tree_pointer item) {
	if (isFullS(s)) {
		fprintf(stderr, "Stack is full.\n");
		fflush(stdout);
	} else {
		s->data[++s->top] = item;
	}
}

tree_pointer popS(Stack *s) {
	if (isEmptyS(s)) {
		fprintf(stderr, "Stack is empty.\n");
		fflush(stdout);
		return NULL;
	} else {
		return s->data[s->top--];
	}
}

void inOrder(tree_pointer ptr) {
	if (ptr) {
		inOrder(ptr->lchild);
		printf("%d ", ptr->data);
		fflush(stdout);
		inOrder(ptr->rchild);
	}
}

void preOrder(tree_pointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preOrder(ptr->lchild);
		preOrder(ptr->rchild);
	}
}

void postOrder(tree_pointer ptr) {
	if (ptr) {
		postOrder(ptr->lchild);
		postOrder(ptr->rchild);
		printf("%d ", ptr->data);
	}
}

void levelOrder(tree_pointer ptr){
	Queue q;
	Queue *qp;
	qp=&q;
	initq(qp);
	if(!ptr) return;
	addQ(qp,ptr);
	for(;;){
		ptr=deleteQueue(qp);
		if(ptr){
			printf("%d",ptr->data);fflush(stdout);
			if(ptr->lchild){
				addQ(qp,ptr->lchild);
			}
			if(ptr->rchild){
				addQ(qp,ptr->rchild);
			}
		}
		else{
			break;
		}
	}
}

void insert(tree_pointer *root, int data) {
	if (*root == NULL) {
		tree_pointer temp = malloc(sizeof(struct node));
		temp->data = data;
		temp->lchild = temp->rchild = NULL;
		*root = temp;
		return;
	}
	printf("Insert to the left or the right of %d? \n", (*root)->data);
	fflush(stdout);
	char str[10];
	scanf("%s", str);
	if (strcmp(str, "left") == 0) {
		insert(&((*root)->lchild), data);
	} else {
		insert(&((*root)->rchild), data);
	}
}

void insert_iter(tree_pointer *root, int data) {
	tree_pointer temp = malloc(sizeof(*temp));
	temp->data = data;
	temp->lchild = temp->rchild = NULL;
	if (*root == NULL) {
		*root = temp;
		return;
	}
	tree_pointer i;
	char str[10];
	for (i = *root; i != NULL;) {
		printf("Insert to the left or right of %d? \n", (i)->data);
		fflush(stdout);
		scanf("%s", str);
		if (strcmp(str, "left") == 0) {
			if (i->lchild == NULL) {
				i->lchild = temp;
				break;
			} else {
				i = i->lchild;
			}
		} else {
			if (i->rchild == NULL) {
				i->rchild = temp;
				break;
			} else {
				i = i->rchild;
			}
		}
	}
}

int search(tree_pointer root, int key) {
	if (root == NULL)
		return 0;
	if (root->data == key)
		return 1;
	int l = search(root->lchild, key);
	int r = search(root->rchild, key);
	return l || r;
}

void inOrder_iter(tree_pointer root) {
	Stack s;
	Stack *sp;
	sp = &s;
	tree_pointer curr = root;
	initS(sp);
	while (!isEmptyS(sp) || curr != NULL) {
		if (curr != NULL) {
			pushS(sp, curr);
			curr = curr->lchild;
		} else {
			curr = popS(sp);
			printf("%d", curr->data);
			fflush(stdout);
			curr = curr->rchild;
		}
	}
}

void preOrder_iter(tree_pointer root) {
	Stack s;
	Stack *sp;
	tree_pointer curr = root;
	sp = &s;
	initS(sp);
	while (!isEmptyS(sp) || curr != NULL) {
		if (curr != NULL) {
			printf("%d", curr->data);
			fflush(stdout);
			pushS(sp, curr);
			curr = curr->lchild;
		} else {
			curr = popS(sp);
			curr = curr->rchild;
		}
	}
}

void postOrder_iter(tree_pointer root) {
	struct stack {
		tree_pointer node;
		int flag;
	};
	tree_pointer curr;
	struct stack s[20];
	int top = -1;
	if (root == NULL) {
		printf("tree is empty. \n");
		fflush(stdout);
		return;
	}
	curr = root;
	for (;;) {
		while (curr != NULL) {
			s[++top].node = curr;
			s[top].flag = 1;
			curr = curr->lchild;
		}
		while (s[top].flag < 0) {
			curr = s[top--].node;
			printf("%d", curr->data);
			fflush(stdout);
			if (top == -1) {
				return;
			}
		}
		curr = s[top].node;
		curr = curr->rchild;
		s[top].flag = -1;
	}
}

int find(int arr[], int instart, int inend, int key) {
	int pos, i = instart, flag = 0;
	printf("INSTART - %d \t INEND - %d \t DATA - %d \n", instart, inend, key);
	fflush(stdout);
	while (i <= inend) {
		if (arr[i] == key) {
			pos = i;
			flag = 1;
			return pos;
		}
		i++;
	}
	if (flag == 0) {
		fprintf(stdout, "NOT FOUND \n");
		fflush(stdout);
	}
}


tree_pointer preToTree(int preorder[], int inorder[], int instart, int inend) {
	tree_pointer root;
	static int preindex = 0;
	int pos = 0;
	if (instart > inend) {
		return NULL;
	}
	root = malloc(sizeof(*root));
	root->lchild = NULL;
	root->rchild = NULL;
	root->data = preorder[preindex++];

	if (instart == inend) {
		return root;
	}
	//CORRECT TILL HERE

	pos = find(inorder, instart, inend, root->data);
	root->lchild = preToTree(preorder, inorder, instart, pos - 1);

	root->rchild = preToTree(preorder, inorder, pos + 1, inend);

	return root;
}

tree_pointer postToTree(int postorder[], int inorder[], int instart, int inend) {
	tree_pointer root;
	static int preindex = 7;
	int pos = 0;
	if (instart > inend) {
		return NULL;
	}
	root = malloc(sizeof(*root));
	root->lchild = NULL;
	root->rchild = NULL;
	root->data = postorder[preindex--];
	printf("INSTART - %d | INEND - %d | PREINDEX - %d | DATA - %d \n", instart,inend,preindex,root->data);fflush(stdout);

	if (instart == inend) {
		return root;
	}
	//CORRECT TILL HERE

	pos = find(inorder, instart, inend, root->data);
	root->rchild = postToTree(postorder, inorder, pos+1, inend);

	root->lchild = postToTree(postorder, inorder, instart, pos-1);

	return root;

}

int main() {
	tree_pointer tree;
	int inorder[] = { 4, 2, 1, 7, 5, 8, 3, 6 };
	int preorder[] = { 4,2,7,8,5,6,3,1 };
	tree = postToTree(preorder, inorder, 0, 7);
	inOrder(tree);
	printf("\n");
	fflush(stdout);
	preOrder(tree);
	printf("\nLEVEL ORDER - \n");fflush(stdout);
	levelOrder(tree);
	return 0;
}

