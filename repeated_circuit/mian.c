#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int move_count = 0;     //�̵�Ƚ�� ī��Ʈ
int compare_count = 0;  //��Ƚ�� ī��Ʈ
int n1;

//��������
void bubble_sort(int list[], int n)
{
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		int SWAP_count = 0;
		for (j = 0; j < i; j++) {	// �յ��� ���ڵ带 ���� �� ��ü

			if (list[j] > list[j + 1]) {
				SWAP(list[j], list[j + 1], temp);
				move_count += 1;
				SWAP_count = 1;
			}
			compare_count += 1;
		}
		//�̵��� ������ ������ �Ϸ�Ȱ������� �ߴ�
		if (SWAP_count == 0) {
			break;
		}
		if (n1 == 0) {
			for (int i = 0; i < 20; i++) {
				printf("%d ", list[i]);
			}
			printf("\n");
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
			printf("\n\n���� ����\n");

		}


		bubble_sort(list_O, 20);
	}
	printf("������ �Ϸ� �Ǿ����ϴ�.\n");
	printf("�̵� Ƚ�� ���: %d\n", move_count / 20);
	printf("�� Ƚ�� ���: %d", compare_count / 20);

	return 0;
}