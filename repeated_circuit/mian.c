#include <stdio.h>
#include <stdlib.h>


int move_count = 0;     //�̵�Ƚ�� ī��Ʈ
int compare_count = 0;  //��Ƚ�� ī��Ʈ
int n1;

// gap ��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last
inc_insertion_sort(int list[], int first, int last, int gap)
{
	int a, i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {

		key =  a = list[i];
		for (j = i - gap; j > first && key < list[j]; j = j - gap) {
			list[j + gap] = list[j];
			move_count += 1;
			
		}
		list[j + gap] = key;	
		if (a != list[i])
			compare_count += 1;
	}
}
// ������
void shell_sort(int list[], int n)   // n = size
{
	
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++) {		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap);

		}
		if (n1 == 0) {
			
			for (int j = 0; j < 20; j++) {
				printf("%d ", list[j]);
			}
			printf("\n");
		}
	}
}


void  main()
{
	for (n1 = 0; n1 < 20; n1++) {
		srand(time(NULL)); // ���� �ʱ�ȭ
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
			printf("\n\n�� ����\n");
		}
	
		shell_sort(list_O, 20);
	}

	printf("\n�̵� Ƚ�� ���: %d\n", move_count / 20);
	printf("�� Ƚ�� ���: %d", compare_count / 20);

	return 0;
}