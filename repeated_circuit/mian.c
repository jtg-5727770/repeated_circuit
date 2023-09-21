#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
	int is_thread; //���� ������ ��ũ�� �������̸� TRUE
} TreeNode;

//��ũ ��� ���Է�
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

//���� �ļ��ڸ� ã�� �Լ� 
TreeNode* find_successor(TreeNode* p)
{
	// q�� p�� ������ ������
	TreeNode* q = p->right;
	// ���� ������ �����Ͱ� NULL�̰ų� �������̸� ������ �����͸� ��ȯ
	if (q == NULL || p->is_thread == 1)
		return q;
	
	// ���� ������ �ڽ��̸� �ٽ� ���� ���� ���� �̵�
	while (q->left != NULL) 
		q = q->left;
	return q;
}

//���� ��ȸ �Լ� 
void thread_inorder(TreeNode* t)
{
	TreeNode* q;
	q = t;
	while (q->left)
		q = q->left; // ���� ���� ���� ����.
	do
	{
		printf("%d ", q->data); // ������ ���
		q = find_successor(q); // �ļ��� �Լ� ȣ��
	} while (q);			// NULL�� �ƴϸ�
}

//�θ� ��� ã�� �Լ�
TreeNode* parent(TreeNode* child) {
	TreeNode* q;
	q = child;
	while (q->left)
		q = q->left; // ���� ���� ���� ����.
	if (q->right->left == q) {  //�������� ���� �ڽ��� �ڽ��ΰ��
		q = q->right;           //�������� ��带 ���
		printf("%d\n", q->data);
	}
	else {                      //�������� �����ڽ��� �ڽ��� �ƴѰ��
		q = q->right->left;     //�������� �̵��� ���
		printf("%d\n", q->data);
	}
}
void  main()
{
	//��� ������ ����
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
	printf("1. ���� ��ȸ ���\n");
	thread_inorder(root);
	printf("\n\n");
	printf("2. Node 4�� �θ�: ");
	parent(&n1);
	printf("3. Node 5�� �θ�: ");
	parent(&n2);
	printf("4. Node 6�� �θ�: ");
	parent(&n4);

	return 0;
}