#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

// 순회를 위한 스택 생성
#define SIZE 100
int top1 = -1;
int top2 = -1;
TreeNode* stack1[SIZE];
TreeNode* stack2[SIZE];

// 첫번째 스택 push 함수
void push1(TreeNode* p)
{
	if (top1 < SIZE - 1)
		stack1[++top1] = p;
}
// 첫번째 스택 pop 함수
TreeNode* pop1()
{
	TreeNode* p = NULL;
	if (top1 >= 0)
		p = stack1[top1--];
	return p;
}
// 두번째 스택 push함수
void push2(TreeNode* p)
{
	if (top2 < SIZE - 1)
		stack2[++top2] = p;
}
// 두번째 스택 pop 함수
TreeNode* pop2()
{
	TreeNode* p = NULL;
	if (top2 >= 0)
		p = stack2[top2--];
	return p;
}
// 전위 순회
void preorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left) {
			push1(root);                  //root를 push
			printf("%d ", root->data);   //root를 출력
		}
		root = pop1();     
		if (!root) break;
		root = root->right;
	}
}
// 중위 순회
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
// 후위 순회
// 후위 순회
void postorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->right) {
			push1(root);
			push2(root);
		}
		root = pop2(); // 두 번째 스택에서 노드를 꺼냅니다.
		if (!root) break;
		root = root->left; // 왼쪽 서브트리로 이동합니다.
	}

	while (top1 >= 0) {
		root = pop1(); // 첫 번째 스택에서 노드를 꺼내면서 출력합니다.
		printf("%d ", root->data);
	}
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