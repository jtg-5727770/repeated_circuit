#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

// push �Լ�
void push(TreeNode* p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}
// pop �Լ�
TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}
// ���� ��ȸ
void preorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left) {
			push(root);
			printf("%d ", root->data);
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}
// ���� ��ȸ
void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("%d ", root->data);
		root = root->right;
	}
}
// ���� ��ȸ
void postorder_iter(TreeNode* root)
{

}

//��ũ ��� ���Է�
TreeNode n1 = { 4, NULL, NULL };
TreeNode n2 = { 5, NULL, NULL };
TreeNode n3 = { 3, &n1, &n2 };
TreeNode n4 = { 6, NULL, NULL };
TreeNode n5 = { 2, &n3, &n4 };
TreeNode n6 = { 10, NULL, NULL };
TreeNode n7 = { 11, NULL, NULL };
TreeNode n8 = { 9, &n6, &n7 };
TreeNode n9 = { 8, NULL, NULL };
TreeNode n10 = { 7, &n9, &n8 };
TreeNode n11 = { 1, &n5, &n10 };
TreeNode* root = &n11;

void  main()
{
	printf("[Linked Tree]\n");
	
	printf("1.���� ��ȸ\n");
	preorder_iter(root);
	printf("\n\n");
	
	printf("2.���� ��ȸ\n");
	inorder_iter(root);
	printf("\n\n");

	printf("3.���� ��ȸ\n");
	postorder_iter(root);
	printf("\n\n");
	
	return 0;
}