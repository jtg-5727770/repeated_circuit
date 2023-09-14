#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

// ��ȸ�� ���� ���� ����
#define SIZE 100
int top1 = -1;
int top2 = -1;
TreeNode* stack1[SIZE];
TreeNode* stack2[SIZE];

// ù��° ���� push �Լ�
void push1(TreeNode* p)
{
	if (top1 < SIZE - 1)
		stack1[++top1] = p;
}
// ù��° ���� pop �Լ�
TreeNode* pop1()
{
	TreeNode* p = NULL;
	if (top1 >= 0)
		p = stack1[top1--];
	return p;
}
// �ι�° ���� push�Լ�
void push2(TreeNode* p)
{
	if (top2 < SIZE - 1)
		stack2[++top2] = p;
}
// �ι�° ���� pop �Լ�
TreeNode* pop2()
{
	TreeNode* p = NULL;
	if (top2 >= 0)
		p = stack2[top2--];
	return p;
}
// ���� ��ȸ
void preorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left) {
			push1(root);                  //root�� push
			printf("%d ", root->data);   //root�� ���
		}
		root = pop1();     
		if (!root) break;
		root = root->right;
	}
}
// ���� ��ȸ
void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push1(root);
		root = pop1();
		if (!root) break;
		printf("%d ", root->data);
		root = root->right;
	}
}
// ���� ��ȸ
// ���� ��ȸ
void postorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->right) {
			push1(root);
			push2(root);
		}
		root = pop2(); // �� ��° ���ÿ��� ��带 �����ϴ�.
		if (!root) break;
		root = root->left; // ���� ����Ʈ���� �̵��մϴ�.
	}

	while (top1 >= 0) {
		root = pop1(); // ù ��° ���ÿ��� ��带 �����鼭 ����մϴ�.
		printf("%d ", root->data);
	}
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