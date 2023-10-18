#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

//���� ���� ���α׷�
/*
// ��� ����ü ����
typedef struct {
	int key;  // ���� ���� �����ϴ� ��� ����ü
} element;

// �� ����ü ����
typedef struct {
	element heap[MAX_ELEMENT];  // ��ҵ��� �����ϴ� �迭
	int heap_size;  // ���� ���� ũ��
} HeapType;

// ���� �Լ�: ���� �����ϰ� �� �ּҸ� ��ȯ�ϴ� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));  // ���� �������� �Ҵ��ϰ� �ʱ�ȭ
}

// �ʱ�ȭ �Լ�: ���� �ʱ�ȭ�ϴ� �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;  // �� ũ�� �ʱ�ȭ
}

// ���� ����� ������ heap_size�� ���� h�� item�� �����ϴ� �Լ�
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);  // ���ο� ��Ҹ� ���� ��ġ�� ã�� ���� �� ũ�� ����

	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  // �θ� ���� �ڸ��� �ٲ���
		i /= 2;
	}
	h->heap[i] = item;  // ���ο� ��带 ����

	// ��尡 �̵��� ������ �� ���� ���
	for (int j = 1; j <= h->heap_size; j++) {
		printf("%d ", h->heap[j].key);  // ���� �� ���¸� ���
	}
	printf("\n");
}

// ���� �Լ�: �ִ��� �����ϰ� ��ȯ�ϴ� �Լ�
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];  // �ִ��� ����
	temp = h->heap[(h->heap_size)--];  // �� ũ�⸦ �����ϰ� ������ ��Ҹ� ����
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �� �� ���� �ڽ� ��带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	// ��尡 �̵��� ������ �� ���� ���
	for (int j = 1; j <= h->heap_size; j++) {
		printf("%d ", h->heap[j].key);  // ���� �� ���¸� ���
	}
	printf("\n");

	return item;  // ������ �ִ� ��ȯ
}

// �켱 ���� ť�� ������ �̿��� ����
void heap_sort(element a[], int n)
{
	int i;
	HeapType* h;

	h = create();  // �� ����
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);  // ���� ��� ����
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);  // �ִ��� �����ϰ� �迭�� ����
	}
	free(h);  // �� �޸� ����
}

#define SIZE 17

int main(void)
{
	element list[SIZE] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86 };

	HeapType* heap;

	heap = create();  // �� ����
	init(heap);

	delete_max_heap(heap);

	heap_sort(list, SIZE);  // �� ���� ����

	for (int i = 0; i < SIZE; i++) {
		printf("%d ", list[i].key);  // ���ĵ� �迭 ���
	}
	printf("\n");

	return 0;
}
*/
//������ �ڵ� ����

// Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int weight;  // ����� ����ġ
    char ch;  // ����� ����
    struct TreeNode* left;  // ���� �ڽ� ���
    struct TreeNode* right;  // ������ �ڽ� ���
} TreeNode;

// ������ Ʈ�� ��� ����ü ����
typedef struct Element {
    TreeNode* ptree;  // Ʈ�� ��忡 ���� ������
    char ch;  // ����
    int key;  // ����ġ
} element;

// �� ����ü ����
typedef struct HeapType {
    element heap[MAX_ELEMENT];  // ��ҵ��� �����ϴ� �迭
    int heap_size;  // ���� ���� ũ��
} HeapType;

// ���� �Լ�: ���� �����ϰ� �� �ּҸ� ��ȯ�ϴ� �Լ�
HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));  // ���� �������� �Ҵ��ϰ� �ʱ�ȭ
}

// �ʱ�ȭ �Լ�: ���� �ʱ�ȭ�ϴ� �Լ�
void init(HeapType* h)
{
    h->heap_size = 0;  // �� ũ�� �ʱ�ȭ
}

// ���� ����� ������ heap_size�� ���� h�� item�� �����ϴ� �Լ�
void insert_min_heap(HeapType* h, element item)
{
    int i;
    i = ++(h->heap_size);  // ���ο� ��Ҹ� ���� ��ġ�� ã�� ���� �� ũ�� ����

    // Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];  // �θ� ���� �ڸ��� �ٲ���
        i /= 2;
    }
    h->heap[i] = item;  // ���ο� ��带 ����

    // ��尡 �̵��� ������ �� ���� ���
    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key);  // ���� �� ���¸� ���
    }
    printf("\n");
}

// ���� �Լ�: �ּڰ��� �����ϰ� ��ȯ�ϴ� �Լ�
element delete_min_heap(HeapType* h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];  // �ּڰ��� ����
    temp = h->heap[(h->heap_size)--];  // �� ũ�⸦ �����ϰ� ������ ��Ҹ� ����
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // ���� ����� �ڽ� ��� �� �� ���� �ڽ� ��带 ã�´�.
        if ((child < h->heap_size) &&
            (h->heap[child].key) > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key) break;
        // �� �ܰ� �Ʒ��� �̵�
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;  // ������ �ּڰ� ��ȯ
}

// ���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// ���� Ʈ�� ���� �Լ�
void destroy_tree(TreeNode* root)
{
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// �ܸ� ��� ���� Ȯ�� �Լ�
int is_leaf(TreeNode* root)
{
    return !(root->left) && !(root->right);
}

// �迭 ��� �Լ�
void print_array(int codes[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// ������ �ڵ� ��� �Լ�
void print_codes(TreeNode* root, int codes[], int top)
{
    // 1�� �����ϰ� ��ȯȣ���Ѵ�.
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }

    // 0�� �����ϰ� ��ȯȣ���Ѵ�.
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }

    // �ܸ�����̸� �ڵ带 ����Ѵ�.
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

// ������ �ڵ� ���� �Լ�
void huffman_tree(int freq[], char ch_list[], int n)
{
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = create();  // �� ����
    init(heap);
    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);  // ���� ��� ����
    }
    for (i = 1; i < n; i++) {
        // �ּڰ��� ������ �� ���� ��带 ����
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        // �� ���� ��带 ��ģ��.
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("// %d+%d->%d \n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);  // ��ģ ��带 ���� ����
    }
    e = delete_min_heap(heap);  // ���� Ʈ��
    print_codes(e.ptree, codes, top);  // ������ �ڵ� ���
    destroy_tree(e.ptree);  // Ʈ�� �޸� ����
    free(heap);  // �� �޸� ����
}

int main(void)
{
    char ch_list[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int freq[] = { 10, 15, 12, 3, 4, 13, 1 };
    huffman_tree(freq, ch_list, 7);  // ������ �ڵ� ���� ����
    return 0;
}