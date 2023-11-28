#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define MAX_SIZE 20
int move_count = 0;     //이동횟수 카운트
int compare_count = 0;  //비교횟수 카운트
int n1;

int sorted[MAX_SIZE]; // 추가 공간이 필요
// i는 정렬된 왼쪽리스트에 대한 인덱스
// j는 정렬된 오른쪽리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스

//합병
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
			compare_count++;
		}
		else {
			sorted[k++] = list[j++];
			
		}

		move_count++;
	}
	if (i > mid) { 	// 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			move_count++;
		}
		compare_count++;
	}
	else { 	// 남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			move_count++;
		}
		compare_count++;
	}

	// 배열 sorted[]의 리스트를 배열 list[]로 복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
	if (n1 == 0) {

		for (int i = 0; i < 20; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");
	}
}

//분할
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;              // 리스트의 균등분할
		merge_sort(list, left, mid);     // 부분리스트 정렬
		merge_sort(list, mid + 1, right);//부분리스트 정렬
		merge(list, left, mid, right);    // 합병
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
			printf("\n\n합병 정렬\n");
		}

		merge_sort(list_O, 0, 19);
	}

	printf("\n이동 횟수 평균: %d\n", move_count / 20);
	printf("비교 횟수 평균: %d", compare_count / 20);

	return 0;
}