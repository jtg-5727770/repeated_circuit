#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

//��ũ ��� ���Է�
TreeNode n1 = { 25, NULL, NULL };
TreeNode n2 = { 16, NULL, &n1 };
TreeNode n3 = { 42, NULL, NULL };
TreeNode n4 = { 46, &n3, NULL };
TreeNode n5 = { 55, NULL, NULL };
TreeNode n6 = { 53, &n4, &n5 };
TreeNode n7 = { 41, &n2, &n6 };
TreeNode n8 = { 62, NULL, NULL };
TreeNode n9 = { 64, NULL, NULL };
TreeNode n10 = { 63, &n8, &n9 };
TreeNode n11 = { 70, NULL, NULL };
TreeNode n12 = { 65, &n10, &n11 };
TreeNode n13 = { 74, &n12, NULL };
TreeNode n14 = { 60, &n7, &n13};
TreeNode* root = &n13;

// �ݺ����� Ž�� �Լ�
TreeNode* search(TreeNode* node, int key)
{
	while (node != NULL) {
		if (key == node->data) return node;
		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; 	// Ž���� �������� ��� NULL ��ȯ
}

void  main()
{
	int k;

	char input[100];
	while (1) {
		printf("=========�޴�=========\n");
		printf("s) �˻�\n");
		printf("i) ��� �߰�\n");
		printf("d) ��� ����\n");
		printf("t) ���� ��ȸ\n");
		printf("l) ��� �߰�(�ݺ�)\n");
		printf("D) ������(�ݺ�)\n");
		printf("c) ����\n");
		printf("�޴��� �����ϼ���: ");
		scanf_s("%s", input, sizeof(input));
		if (strlen(input) == 1) {
			char c = input[0];
			switch (c) {
			case 's':
				printf("�˻��� �� �Է�: ");
				scanf_s("%d", &k);
				if (search(root, 30) != NULL)
					printf("�˻� ����: %d\n", k);
				else
					printf("%d�� Ʈ���� �����ϴ�.\n",k);
				break;
			case 'i':
				
				break;
			case 'd':
				
				break;
			case 't':
				
				break;
			case 'l':
				
				break;
			case 'D':

				break;
			case 'c':
				printf("���α׷��� �����մϴ�.\n");
				exit(0);
			default:
				printf("�ٽ� �������ּ���.\n");
				while (getchar() != '\n');
			}
		}
		else {
			printf("�ٽ� �������ּ���.\n");

		}

	}
	return 0;
}