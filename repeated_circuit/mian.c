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

// push 함수
void push(TreeNode* p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}
// pop 함수
TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}
// 전위 순회
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
// 중위 순회
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
// 후위 순회
void postorder_iter(TreeNode* root)
{

}

//링크 노드 값입력
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
	
	printf("1.전위 순회\n");
	preorder_iter(root);
	printf("\n\n");
	
	printf("2.중위 순회\n");
	inorder_iter(root);
	printf("\n\n");

	printf("3.후위 순회\n");
	postorder_iter(root);
	printf("\n\n");
	
	return 0;
}