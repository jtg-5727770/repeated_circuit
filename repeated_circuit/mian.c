#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

//히프 정렬 프로그램
/*
// 요소 구조체 정의
typedef struct {
	int key;  // 정수 값을 저장하는 요소 구조체
} element;

// 힙 구조체 정의
typedef struct {
	element heap[MAX_ELEMENT];  // 요소들을 저장하는 배열
	int heap_size;  // 힙의 현재 크기
} HeapType;

// 생성 함수: 힙을 생성하고 그 주소를 반환하는 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));  // 힙을 동적으로 할당하고 초기화
}

// 초기화 함수: 힙을 초기화하는 함수
void init(HeapType* h)
{
	h->heap_size = 0;  // 힙 크기 초기화
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입하는 함수
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);  // 새로운 요소를 넣을 위치를 찾기 위해 힙 크기 증가

	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  // 부모 노드와 자리를 바꿔줌
		i /= 2;
	}
	h->heap[i] = item;  // 새로운 노드를 삽입

	// 노드가 이동될 때마다 힙 상태 출력
	for (int j = 1; j <= h->heap_size; j++) {
		printf("%d ", h->heap[j].key);  // 현재 힙 상태를 출력
	}
	printf("\n");
}

// 삭제 함수: 최댓값을 삭제하고 반환하는 함수
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];  // 최댓값을 저장
	temp = h->heap[(h->heap_size)--];  // 힙 크기를 감소하고 마지막 요소를 저장
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식 노드 중 더 작은 자식 노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	// 노드가 이동될 때마다 힙 상태 출력
	for (int j = 1; j <= h->heap_size; j++) {
		printf("%d ", h->heap[j].key);  // 현재 힙 상태를 출력
	}
	printf("\n");

	return item;  // 삭제된 최댓값 반환
}

// 우선 순위 큐인 히프를 이용한 정렬
void heap_sort(element a[], int n)
{
	int i;
	HeapType* h;

	h = create();  // 힙 생성
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);  // 힙에 요소 삽입
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);  // 최댓값을 삭제하고 배열에 저장
	}
	free(h);  // 힙 메모리 해제
}

#define SIZE 17

int main(void)
{
	element list[SIZE] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86 };

	HeapType* heap;

	heap = create();  // 힙 생성
	init(heap);

	delete_max_heap(heap);

	heap_sort(list, SIZE);  // 힙 정렬 수행

	for (int i = 0; i < SIZE; i++) {
		printf("%d ", list[i].key);  // 정렬된 배열 출력
	}
	printf("\n");

	return 0;
}
*/
//히프만 코드 생성

// 트리 노드 구조체 정의
typedef struct TreeNode {
    int weight;  // 노드의 가중치
    char ch;  // 노드의 문자
    struct TreeNode* left;  // 왼쪽 자식 노드
    struct TreeNode* right;  // 오른쪽 자식 노드
} TreeNode;

// 허프만 트리 요소 구조체 정의
typedef struct Element {
    TreeNode* ptree;  // 트리 노드에 대한 포인터
    char ch;  // 문자
    int key;  // 가중치
} element;

// 힙 구조체 정의
typedef struct HeapType {
    element heap[MAX_ELEMENT];  // 요소들을 저장하는 배열
    int heap_size;  // 힙의 현재 크기
} HeapType;

// 생성 함수: 힙을 생성하고 그 주소를 반환하는 함수
HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));  // 힙을 동적으로 할당하고 초기화
}

// 초기화 함수: 힙을 초기화하는 함수
void init(HeapType* h)
{
    h->heap_size = 0;  // 힙 크기 초기화
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입하는 함수
void insert_min_heap(HeapType* h, element item)
{
    int i;
    i = ++(h->heap_size);  // 새로운 요소를 넣을 위치를 찾기 위해 힙 크기 증가

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];  // 부모 노드와 자리를 바꿔줌
        i /= 2;
    }
    h->heap[i] = item;  // 새로운 노드를 삽입

    // 노드가 이동될 때마다 힙 상태 출력
    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key);  // 현재 힙 상태를 출력
    }
    printf("\n");
}

// 삭제 함수: 최솟값을 삭제하고 반환하는 함수
element delete_min_heap(HeapType* h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];  // 최솟값을 저장
    temp = h->heap[(h->heap_size)--];  // 힙 크기를 감소하고 마지막 요소를 저장
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // 현재 노드의 자식 노드 중 더 작은 자식 노드를 찾는다.
        if ((child < h->heap_size) &&
            (h->heap[child].key) > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key) break;
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;  // 삭제된 최솟값 반환
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root)
{
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 단말 노드 여부 확인 함수
int is_leaf(TreeNode* root)
{
    return !(root->left) && !(root->right);
}

// 배열 출력 함수
void print_array(int codes[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 허프만 코드 출력 함수
void print_codes(TreeNode* root, int codes[], int top)
{
    // 1을 저장하고 순환호출한다.
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }

    // 0을 저장하고 순환호출한다.
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }

    // 단말노드이면 코드를 출력한다.
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

// 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n)
{
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = create();  // 힙 생성
    init(heap);
    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);  // 힙에 요소 삽입
    }
    for (i = 1; i < n; i++) {
        // 최솟값을 가지는 두 개의 노드를 삭제
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        // 두 개의 노드를 합친다.
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("// %d+%d->%d \n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);  // 합친 노드를 힙에 삽입
    }
    e = delete_min_heap(heap);  // 최종 트리
    print_codes(e.ptree, codes, top);  // 허프만 코드 출력
    destroy_tree(e.ptree);  // 트리 메모리 해제
    free(heap);  // 힙 메모리 해제
}

int main(void)
{
    char ch_list[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int freq[] = { 10, 15, 12, 3, 4, 13, 1 };
    huffman_tree(freq, ch_list, 7);  // 허프만 코드 생성 수행
    return 0;
}