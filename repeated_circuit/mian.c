#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 1000
#define INF 1000

int parent[MAX_VERTICES];		// 부모 노드
// 초기화
void set_init(int n)
{
	for (int i = 1; i < n; i++)
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}
// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

struct Edge {			// 간선을 나타내는 구조체
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// 간선의 개수
	
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// qsort를 이용한 kruskal의 최소 비용 신장 트리 프로그램
void qsort_kruskal(GraphType* g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n);				// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("qsort를 이용한 크루스칼 최소 신장 트리 알고리즘 \n");
	int i = 0;
	while (edge_accepted < (g->n - 1))	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
}

// MinHeap의 힙 조건을 유지하기 위한 함수
void heapify(struct Edge* arr, int n, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// 왼쪽 자식 노드와 현재 노드 비교하여 더 작은 노드를 smallest에 저장
	if (left < n && arr[left].weight < arr[smallest].weight)
		smallest = left;
	// 오른쪽 자식 노드와 smallest를 비교하여 더 작은 노드를 smallest에 저장
	if (right < n && arr[right].weight < arr[smallest].weight)
		smallest = right;

	// 현재 노드(i)가 smallest와 다를 경우 교환하고 재귀적으로 호출하여 힙 조건 유지
	if (smallest != i) {
		struct Edge temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
		heapify(arr, n, smallest);
	}
}
// MinHeap 빌드
void build_heap(struct Edge* arr, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		// 노드들을 차례로 heapify하여 MinHeap을 생성
		heapify(arr, n, i);
	}
}
// MinHeap에서 최소값 추출
struct Edge extract_min(struct Edge* arr, int* n) {
	if (*n <= 0) {
		struct Edge minEdge = { 0, 0, INF };
		return minEdge;
	}

	// 최소값은 항상 MinHeap의 루트 노드에 위치
	struct Edge minEdge = arr[0];
	// 루트 노드에 가장 마지막 노드를 복사하고 MinHeap 크기 감소
	arr[0] = arr[*n - 1];
	(*n)--;
	// 변경된 루트 노드로부터 heapify 호출하여 힙 조건 유지
	heapify(arr, *n, 0);

	return minEdge;
}
// MinHeap을 이용한 kruskal의 최소 비용 신장 트리 프로그램
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

	printf("MinHeap을 사용한 크루스칼 최소 신장 트리 알고리즘\n");
	while (edge_accepted < (g->n - 1)) {
		e = extract_min(minHeap, &minHeapSize);
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			// 간선 선택 및 출력
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
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
