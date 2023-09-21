#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
	int is_thread; //만약 오른쪽 링크가 스레드이면 TRUE
} TreeNode;

//링크 노드 값입력
TreeNode n1 = { 4, NULL, NULL, 0 };
TreeNode n2 = { 5, NULL, NULL, 0 };
TreeNode n3 = { 3, &n1, &n2, 0 };
TreeNode n4 = { 6, NULL, NULL, 0 };
TreeNode n5 = { 2, &n3, &n4, 0 };
TreeNode n6 = { 10, NULL, NULL, 0 };
TreeNode n7 = { 11, NULL, NULL, 0 };
TreeNode n8 = { 9, &n6, &n7, 0 };
TreeNode n9 = { 8, NULL, NULL, 0 };
TreeNode n10 = { 7, &n9, &n8, 0 };
TreeNode n11 = { 1, &n5, &n10, 0 };
TreeNode* root = &n11;

//중위 후속자를 찾는 함수 
TreeNode* find_successor(TreeNode* p)
{
	// q는 p의 오른쪽 포인터
	TreeNode* q = p->right;
	// 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환
	if (q == NULL || p->is_thread == 1)
		return q;
	
	// 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
	while (q->left != NULL) 
		q = q->left;
	return q;
}

//중위 순회 함수 
void thread_inorder(TreeNode* t)
{
	TreeNode* q;
	q = t;
	while (q->left)
		q = q->left; // 가장 왼쪽 노드로 간다.
	do
	{
		printf("%d ", q->data); // 데이터 출력
		q = find_successor(q); // 후속자 함수 호출
	} while (q);			// NULL이 아니면
}

//부모 노드 찾는 함수
TreeNode* parent(TreeNode* child) {
	TreeNode* q;
	q = child;
	while (q->left)
		q = q->left; // 가장 왼쪽 노드로 간다.
	if (q->right->left == q) {  //스레드의 왼쪽 자식이 자신인경우
		q = q->right;           //스레드한 노드를 출력
		printf("%d\n", q->data);
	}
	else {                      //스레드의 왼쪽자식이 자신이 아닌경우
		q = q->right->left;     //왼쪽으로 이동후 출력
		printf("%d\n", q->data);
	}
}
void  main()
{
	//노드 스레드 설정
	n1.right = &n3;
	n1.is_thread = 1;
	
	n2.right = &n5;
	n2.is_thread = 1;
	
	n4.right = &n11;
	n4.is_thread = 1;
	
	n9.right = &n10;
	n9.is_thread = 1;
	
	n6.right = &n8;
	n6.is_thread = 1;
	printf("1. 중위 순회 결과\n");
	thread_inorder(root);
	printf("\n\n");
	printf("2. Node 4의 부모: ");
	parent(&n1);
	printf("3. Node 5의 부모: ");
	parent(&n2);
	printf("4. Node 6의 부모: ");
	parent(&n4);

	return 0;
}