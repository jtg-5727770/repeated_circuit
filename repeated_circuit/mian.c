#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

//링크 노드 값입력
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

// 반복적인 탐색 함수
TreeNode* search(TreeNode* node, int key)
{
	while (node != NULL) {
		if (key == node->data) return node;
		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; 	// 탐색에 실패했을 경우 NULL 반환
}

void  main()
{
	int k;

	char input[100];
	while (1) {
		printf("=========메뉴=========\n");
		printf("s) 검색\n");
		printf("i) 노드 추가\n");
		printf("d) 노드 삭제\n");
		printf("t) 중위 순회\n");
		printf("l) 노드 추가(반복)\n");
		printf("D) 노드삭제(반복)\n");
		printf("c) 종료\n");
		printf("메뉴를 선택하세요: ");
		scanf_s("%s", input, sizeof(input));
		if (strlen(input) == 1) {
			char c = input[0];
			switch (c) {
			case 's':
				printf("검색할 값 입력: ");
				scanf_s("%d", &k);
				if (search(root, 30) != NULL)
					printf("검색 성공: %d\n", k);
				else
					printf("%d는 트리에 없습니다.\n",k);
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
				printf("프로그램을 종료합니다.\n");
				exit(0);
			default:
				printf("다시 선택해주세요.\n");
				while (getchar() != '\n');
			}
		}
		else {
			printf("다시 선택해주세요.\n");

		}

	}
	return 0;
}