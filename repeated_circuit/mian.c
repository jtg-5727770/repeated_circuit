#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int move_count = 0;     //이동횟수 카운트
int compare_count = 0;  //비교횟수 카운트
int n1;

//버블정렬
void bubble_sort(int list[], int n)
{
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		int SWAP_count = 0;
		for (j = 0; j < i; j++) {	// 앞뒤의 레코드를 비교한 후 교체

			if (list[j] > list[j + 1]) {
				SWAP(list[j], list[j + 1], temp);
				move_count += 1;
				SWAP_count = 1;
			}
			compare_count += 1;
		}
		//이동이 없으면 정렬이 완료된것임으로 중단
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
	srand(time(NULL)); // 난수 초기화
	for (n1 = 0; n1 < 20; n1++) {
		
		int list_O[20];
		int random = 0; // 정수형 변수 선언
		for (int i = 0; i < 20; i++) {
			random = rand() % 100; // 난수 생성
			list_O[i] = random;
		}
		if (n1 == 0) {
			printf("초기 리스트\n");
			for (int i = 0; i < 20; i++) {
				printf("%d ", list_O[i]);

			}
			printf("\n\n버블 정렬\n");

		}


		bubble_sort(list_O, 20);
	}
	printf("정렬이 완료 되었습니다.\n");
	printf("이동 횟수 평균: %d\n", move_count / 20);
	printf("비교 횟수 평균: %d", compare_count / 20);

	return 0;
}