/*
8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define NO_MEMORY_ERROR -1

typedef struct treeNode* treePointer;
struct treeNode
{
	int value;
	treePointer left;
	treePointer right;
};
treePointer InsertElement(int, treePointer);
treePointer AllocateNew(int);
int InOrder(treePointer);
int PostOrder(treePointer);
int PreOrder(treePointer);
int Height(treePointer);
int CurrentLevel(treePointer, int );
treePointer FindElement(int, treePointer);

int main()
{
	treePointer root = NULL;
	int choice = 0, element;
	treePointer temp = NULL;

	while (1) {
		printf("----------\n");
		printf("Odaberi:\n");
		printf("1 - unos novog elementa u stablo\n");
		printf("2 - ispis inorder stabla\n");
		printf("3 - ispis postorder stabla\n");
		printf("4 - ispis preorder stabla\n");
		printf("5 - trazenje elementa stabla\n");
		printf("6 - izlaz\n");
		printf("-----\n");
		printf("> ");
		scanf("%d", &choice);
		printf("-----\n");
        switch (choice)
		{
		case 1:
			printf("Unesi element koji zelis unijeti u stablo: ");
			scanf("%d", &element);
			root = InsertElement(element, root);
            if (root == NULL)
                return NO_MEMORY_ERROR;
			break;
		case 2:
            if (root == NULL)
                printf("Stablo je prazno.\n");
            else {
			    printf("Ispis InOrder: ");
			    InOrder(root);
            }
			break;
		case 3:
            if (root == NULL)
                printf("Stablo je prazno.\n");
            else {
			    printf("Ispis PostOrder: ");
			    PostOrder(root);
            }
			break;
		case 4:
            if (root == NULL)
                printf("Stablo je prazno.\n");
            else {
			    printf("Ispis PreOrder: ");
			    PreOrder(root);
            }
			break;
		case 5:
			printf("Unesi element koji trazis u stablu: ");
			scanf("%d", &element);
			temp = FindElement(element, root);
			if (temp == NULL)
                printf("Element %d se ne nalazi u stablu!\n", element);
            else
				printf("Element %d se nalazi na adresi %p\n", temp->value, temp);
			break;
        case 6:
            return 0;
        }
		printf("\n");
    }

	return 0;
}

treePointer AllocateNew(int element)
{
	treePointer newNode = malloc(sizeof(struct treeNode));
    if (newNode == NULL) {
        printf("Nije moguce alocirati memoriju!");
        return NULL;
    }
  	newNode->value = element;
  	newNode->left = NULL;
  	newNode->right = NULL;
  	return newNode;
}

treePointer InsertElement(int element,treePointer root)
{
	if(root == NULL) {
        return AllocateNew(element);
	}
	if(root->value <= element) {
        root->right = InsertElement(element,root->right);
    }
	else if(root->value > element) {
        root->left = InsertElement(element,root->left);
    }
	return root;
}

int InOrder(treePointer root)
{
	if (root == NULL) {
		return 0;
	}
   	InOrder(root->left);
   	printf("%d ", root->value);
   	InOrder(root->right);
	return 0;
}

int PostOrder(treePointer root)
{
	if (root == NULL) {
		return 0;
	}
  	PostOrder(root->left);
  	PostOrder(root->right);
  	printf("%d ", root->value);
	return 0;
}

int PreOrder(treePointer root)
{
	if (root == NULL) {
		return 0;
	}
  	printf("%d ", root->value);
  	PreOrder(root->left);
  	PreOrder(root->right);
	return 0;
}

int CurrentLevel(treePointer root, int level)
{
    if (root == NULL) {
        return 0;
    }
    if (level == 1) {
        printf("%d ", root->value);
        return 0;
    }
    CurrentLevel(root->left, level - 1);
    CurrentLevel(root->right, level - 1);
    return 0;
}

int Height(treePointer root)
{
    if (root == NULL)
        return 0;

    int lheight = Height(root->left);
    int rheight = Height(root->right);

    if (lheight > rheight)
        return (lheight + 1);
    else
        return (rheight + 1);
}

treePointer FindElement(int element, treePointer root)
{
	if (root == NULL)
		return NULL;

    if (element == root->value)
        return root;
    else if (element < root->value)
		return FindElement(element, root->left);
	else
		return FindElement(element, root->right);
}
