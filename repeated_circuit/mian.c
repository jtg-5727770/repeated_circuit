#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 1000
#define INF 1000

int parent[MAX_VERTICES];		// �θ� ���
// �ʱ�ȭ
void set_init(int n)
{
	for (int i = 1; i < n; i++)
		parent[i] = -1;
}
// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}
// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// ��� a�� ��Ʈ�� ã�´�. 
	int root2 = set_find(b);	// ��� b�� ��Ʈ�� ã�´�. 
	if (root1 != root2) 	// ���Ѵ�. 
		parent[root1] = root2;
}

struct Edge {			// ������ ��Ÿ���� ����ü
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// ������ ����
	
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	g->n = g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// qsort�� �̿��� kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void qsort_kruskal(GraphType* g)
{
	int edge_accepted = 0;	// ������� ���õ� ������ ��	
	int uset, vset;			// ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(g->n);				// ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("qsort�� �̿��� ũ�罺Į �ּ� ���� Ʈ�� �˰��� \n");
	int i = 0;
	while (edge_accepted < (g->n - 1))	// ������ �� < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// ���� u�� ���� ��ȣ 
		vset = set_find(e.end);		// ���� v�� ���� ��ȣ
		if (uset != vset) {			// ���� ���� ������ �ٸ���
			printf("���� (%d,%d) %d ����\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
		}
		i++;
	}
}

// MinHeap�� �� ������ �����ϱ� ���� �Լ�
void heapify(struct Edge* arr, int n, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// ���� �ڽ� ���� ���� ��� ���Ͽ� �� ���� ��带 smallest�� ����
	if (left < n && arr[left].weight < arr[smallest].weight)
		smallest = left;
	// ������ �ڽ� ���� smallest�� ���Ͽ� �� ���� ��带 smallest�� ����
	if (right < n && arr[right].weight < arr[smallest].weight)
		smallest = right;

	// ���� ���(i)�� smallest�� �ٸ� ��� ��ȯ�ϰ� ��������� ȣ���Ͽ� �� ���� ����
	if (smallest != i) {
		struct Edge temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
		heapify(arr, n, smallest);
	}
}
// MinHeap ����
void build_heap(struct Edge* arr, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		// ������ ���ʷ� heapify�Ͽ� MinHeap�� ����
		heapify(arr, n, i);
	}
}
// MinHeap���� �ּҰ� ����
struct Edge extract_min(struct Edge* arr, int* n) {
	if (*n <= 0) {
		struct Edge minEdge = { 0, 0, INF };
		return minEdge;
	}

	// �ּҰ��� �׻� MinHeap�� ��Ʈ ��忡 ��ġ
	struct Edge minEdge = arr[0];
	// ��Ʈ ��忡 ���� ������ ��带 �����ϰ� MinHeap ũ�� ����
	arr[0] = arr[*n - 1];
	(*n)--;
	// ����� ��Ʈ ���κ��� heapify ȣ���Ͽ� �� ���� ����
	heapify(arr, *n, 0);

	return minEdge;
}
// MinHeap�� �̿��� kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void minheap_kruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;
	struct Edge minHeap[2*MAX_VERTICES];
	int minHeapSize = 0;

	set_init(g->n);
	for (int i = 0; i < g->n; i++) {
		minHeap[minHeapSize++] = g->edges[i];
	}

	build_heap(minHeap, minHeapSize);

	printf("MinHeap�� ����� ũ�罺Į �ּ� ���� Ʈ�� �˰���\n");
	while (edge_accepted < (g->n - 1)) {
		e = extract_min(minHeap, &minHeapSize);
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			// ���� ���� �� ���
			printf("���� (%d,%d) %d ����\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
	}
}
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	g->n = 11;
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);

	//qsort_kruskal(g);
	//free(g);

	minheap_kruskal(g);
	free(g);
	return 0;
}
