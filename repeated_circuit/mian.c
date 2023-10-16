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

// ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}
// ��尡 �̵��� Ƚ���� ī��Ʈ�� ��������
int count;

// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_max_heap(HeapType* h, element item)
{
	element temp;
	int i;
	i = ++(h->heap_size);

	h->heap[i] = item; //����
	if (i > 10) {
		for (int j = 1; j <= h->heap_size; j++) {
			printf("%d ", h->heap[j].key);
		}
		printf("\n");
	}
	//  �θ� ���� ��ü�ϸ鼭 �ö�
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		if (item.key > h->heap[i / 2].key) {
			temp = h->heap[i / 2];
			h->heap[i / 2] = h->heap[i];
			h->heap[i] = temp;
			i /= 2;
			count++;
		}
		// ��尡 �̵��ɶ����� �� ���� ���
		for (int j = 1; j <= h->heap_size; j++) {
			printf("%d ", h->heap[j].key);
		}
		printf("\n");
	}

}
// ���� �Լ�
element delete_max_heap(HeapType* h, int key) {
	
	int parent = -1;
	int child;
	element item, temp;
	
	// �־��� key ���� ��ġ�ϴ� ��带 ã��
	for (int i = 1; i <= h->heap_size; i++) {
		if (h->heap[i].key == key) {
			parent = i; //parent�� key���� ����
			break;
		}
	}
	 // ������ ��ġ�ϴ� ���� ��ã�� ��� (heap�� ���� ���� ���)
	if (parent == -1) {
		printf("�ش� ���� ã�� �� �����ϴ�.\n");
		item.key = -1; // ���� ó���� ���� ��
		return item;
	}

	item = h->heap[parent];           // ������ ���� item�� ����
	temp = h->heap[(h->heap_size)--]; // ������ ��带 temp�� �ű�
	child = 2 * parent;
	h->heap[parent] = temp;
	count++;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
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

// Ʈ�� ������ ����Լ�
void print_heap(HeapType* h)
{
	int i;
	int j = 1;
	int level = 1; // ���� ����
	printf("\nƮ�� ������ ���");
	for (i = 1; i <= h->heap_size; i++) {
		// ���� ���� �� ����
		if (i == level) {
			printf("\n[%d] ", j);
			j++;
			level *= 2; // ���� ������ ù ��° ���
		}
		// ����� Ű �� ���
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}


int main() {
	element e1 = { 90 }, e2 = { 89 }, e3 = { 70 }, e4 = { 36 }, e5 = { 75 }, e6 = { 63 }, e7 = { 65 }, e8 = { 21 }, e9 = { 18 }, e10 = { 15 };

	HeapType* heap;

	heap = create(); 	// ���� ����
	init(heap);	        // �ʱ�ȭ

	//����
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
		printf("\n=========�޴�=========\n");
		printf("i) ��� �߰�\n");
		printf("d) ��� ����\n");
		printf("p) ������ ���\n");
		printf("c) ����\n");
		printf("�޴��� �����ϼ���: ");
		scanf_s("%s", input, sizeof(input));
		if (strlen(input) == 1) {
			char c = input[0];

			switch (c) {
			case 'i':
				printf("�߰��� �� �Է�: ");
				scanf_s("%d", &k);
				element ek1 = { k };
				count = 0;
				insert_max_heap(heap, ek1);
				printf("�̵��� ����� Ƚ��: %d\n", count);
				break;

			case 'd':
				printf("������ �� �Է�: ");
				scanf_s("%d", &k);
				count = 0;
				delete_max_heap(heap, k);
				printf("�̵��� ����� Ƚ��: %d\n", count);
				break;

			case 'p':
				print_heap(heap);
				break;

			case 'c':
				printf("���α׷��� �����մϴ�.\n");
				free(heap);
				return 0;
			default:
				printf("�ٽ� �������ּ���.\n");
				while (getchar() != '\n');
			}
		}
		else {
			printf("�ٽ� �������ּ���.\n");

		}

	}

}