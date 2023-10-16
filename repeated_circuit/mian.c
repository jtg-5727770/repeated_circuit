#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 노드가 이동된 횟수를 카운트할 전역변수
int count;

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item)
{
	element temp;
	int i;
	i = ++(h->heap_size);

	h->heap[i] = item; //삽입
	if (i > 10) {
		for (int j = 1; j <= h->heap_size; j++) {
			printf("%d ", h->heap[j].key);
		}
		printf("\n");
	}
	//  부모 노드와 교체하면서 올라감
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		if (item.key > h->heap[i / 2].key) {
			temp = h->heap[i / 2];
			h->heap[i / 2] = h->heap[i];
			h->heap[i] = temp;
			i /= 2;
			count++;
		}
		// 노드가 이동될때마다 힙 상태 출력
		for (int j = 1; j <= h->heap_size; j++) {
			printf("%d ", h->heap[j].key);
		}
		printf("\n");
	}

}
// 삭제 함수
element delete_max_heap(HeapType* h, int key) {
	
	int parent = -1;
	int child;
	element item, temp;
	
	// 주어진 key 값과 일치하는 노드를 찾음
	for (int i = 1; i <= h->heap_size; i++) {
		if (h->heap[i].key == key) {
			parent = i; //parent에 key값을 저장
			break;
		}
	}
	 // 위에서 일치하는 값을 못찾은 경우 (heap에 값이 없는 경우)
	if (parent == -1) {
		printf("해당 값을 찾을 수 없습니다.\n");
		item.key = -1; // 예외 처리를 위한 값
		return item;
	}

	item = h->heap[parent];           // 삭제할 값을 item에 옯김
	temp = h->heap[(h->heap_size)--]; // 마지막 노드를 temp에 옮김
	child = 2 * parent;
	h->heap[parent] = temp;
	count++;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) {
			child++;
		}
		if (temp.key >= h->heap[child].key) {
			break;
		}
		h->heap[parent] = temp;
		for (int j = 1; j <= h->heap_size; j++) {
			printf("%d ", h->heap[j].key);
		}
		printf("\n");
		count++;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
		h->heap[parent] = temp;
	}
	for (int j = 1; j <= h->heap_size; j++) {
		printf("%d ", h->heap[j].key);
	}
	printf("\n");
	return item;
}

// 트리 레벨별 출력함수
void print_heap(HeapType* h)
{
	int i;
	int j = 1;
	int level = 1; // 현재 레벨
	printf("\n트리 레벨별 출력");
	for (i = 1; i <= h->heap_size; i++) {
		// 레벨 변경 시 개행
		if (i == level) {
			printf("\n[%d] ", j);
			j++;
			level *= 2; // 다음 레벨의 첫 번째 노드
		}
		// 노드의 키 값 출력
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}


int main() {
	element e1 = { 90 }, e2 = { 89 }, e3 = { 70 }, e4 = { 36 }, e5 = { 75 }, e6 = { 63 }, e7 = { 65 }, e8 = { 21 }, e9 = { 18 }, e10 = { 15 };

	HeapType* heap;

	heap = create(); 	// 히프 생성
	init(heap);	        // 초기화

	//삽입
	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);
	insert_max_heap(heap, e4);
	insert_max_heap(heap, e5);
	insert_max_heap(heap, e6);
	insert_max_heap(heap, e7);
	insert_max_heap(heap, e8);
	insert_max_heap(heap, e9);
	insert_max_heap(heap, e10);

	int k;
	char input[100];
	while (1) {
		printf("\n=========메뉴=========\n");
		printf("i) 노드 추가\n");
		printf("d) 노드 삭제\n");
		printf("p) 레벨별 출력\n");
		printf("c) 종료\n");
		printf("메뉴를 선택하세요: ");
		scanf_s("%s", input, sizeof(input));
		if (strlen(input) == 1) {
			char c = input[0];

			switch (c) {
			case 'i':
				printf("추가할 값 입력: ");
				scanf_s("%d", &k);
				element ek1 = { k };
				count = 0;
				insert_max_heap(heap, ek1);
				printf("이동된 노드의 횟수: %d\n", count);
				break;

			case 'd':
				printf("삭제할 값 입력: ");
				scanf_s("%d", &k);
				count = 0;
				delete_max_heap(heap, k);
				printf("이동된 노드의 횟수: %d\n", count);
				break;

			case 'p':
				print_heap(heap);
				break;

			case 'c':
				printf("프로그램을 종료합니다.\n");
				free(heap);
				return 0;
			default:
				printf("다시 선택해주세요.\n");
				while (getchar() != '\n');
			}
		}
		else {
			printf("다시 선택해주세요.\n");

		}

	}

}