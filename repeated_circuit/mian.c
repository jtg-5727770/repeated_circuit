#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define MAX_SIZE 20
int move_count = 0;     //�̵�Ƚ�� ī��Ʈ
int compare_count = 0;  //��Ƚ�� ī��Ʈ
int n1;

int sorted[MAX_SIZE]; // �߰� ������ �ʿ�
// i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
// j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
// k�� ���ĵ� ����Ʈ�� ���� �ε���

//�պ�
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
			compare_count++;
		}
		else {
			sorted[k++] = list[j++];
			compare_count++;
		}

		move_count++;
	}
	if (i > mid) { 	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			move_count++;
		}

	}
	else { 	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			move_count++;
		}

	}

	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� ����
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
	if (n1 == 0) {

		for (int i = 0; i < 20; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");
	}
}

//��� ���� 
void merge_sort1(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		//���
		mid = (left + right) / 2;            // ����Ʈ�� �յ����
		merge_sort1(list, left, mid);     // �κи���Ʈ ����
		merge_sort1(list, mid + 1, right);//�κи���Ʈ ����

		merge(list, left, mid, right);    // �պ�
	}
}
//�ݺ� ����
void merge_sort2(int list[], int left, int right) {
	int mid;
	int stack[MAX_SIZE]; // ����
	int top = -1;

	stack[++top] = left;
	stack[++top] = right;

	while (top >= 0) {
		right = stack[top--];
		left = stack[top--];

		if (left < right) {
			mid = (left + right) / 2;

			stack[++top] = left;
			stack[++top] = mid;

			stack[++top] = mid + 1;
			stack[++top] = right;

			merge(list, left, mid, right);
		}
	}
}
void  main()
{
	srand(time(NULL)); // ���� �ʱ�ȭ
	for (n1 = 0; n1 < 20; n1++) {

		int list_O[20];
		int random = 0; // ������ ���� ����
		for (int i = 0; i < 20; i++) {
			random = rand() % 100; // ���� ����
			list_O[i] = random;
		}
		if (n1 == 0) {
			printf("�ʱ� ����Ʈ\n");
			for (int i = 0; i < 20; i++) {
				printf("%d ", list_O[i]);
			}
			printf("\n\n�պ� ����\n");
		}
		// ���
		//merge_sort1(list_O, 0, 19);
		// �ݺ�
		merge_sort2(list_O, 0, 19);
	}

	printf("\n�̵� Ƚ�� ���: %d\n", move_count / 20);
	printf("�� Ƚ�� ���: %d", compare_count / 20);

	return 0;
}