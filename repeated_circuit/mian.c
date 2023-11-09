
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100	
#define INF	1000000	//무한대 (연결이 없는 경우) 


int distance[MAX_VERTICES]; // 시작정점으로부터의 최단경로 거리 
int found[MAX_VERTICES];		// 방문한 정점 표시 
int found_list[MAX_VERTICES];  // 탐색 성공 순서를 저장할 리스트
int found_list1[MAX_VERTICES];
int j = 0;
int j1 = 0;
// 인접 배열방식 그래프
typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} Mat_GraphType;

// 탐색하며 min값 확인
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	found_list[j] = minpos + 1;
	j++;
	return minpos; // 최단 거리를 가진 정점의 인덱스 반환
}

void print_status(Mat_GraphType* g) {
	printf("Disdtance: ");
	for (int i = 0; i < g->n; i++)
	{
		if (distance[i] != INF) {
			printf("%d ", distance[i]);
		}
		else {
			printf("* ");
		}

	}
	printf("\n\n");
}

// 최소거리 구하기
void shortest_path(Mat_GraphType* g, int start)
{
	printf("인접 배열 방식\n");
	int i, u, w;
	for (i = 0; i < g->n; i++) // 초기화 
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		
	}
	found[start] = TRUE;    // 시작 정점 방문 표시 
	distance[start] = 0;      // 시작 정점 거리 0
	found_list[j] = start + 1;
	j++;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found); // min값 확인
		
		found[u] = TRUE;  // 최소거리 정점 방문표시
		for (w = 0; w < g->n; w++) {  //최소거리 업데이트를 하기위한 반복
			if (!found[w])  // 방문하지 않았고
				if (distance[u] + g->weight[u][w] < distance[w]) // 새로 찾은 거리가 현재최소거리보다 작은경우 
					distance[w] = distance[u] + g->weight[u][w]; // 최소거리 업데이트
					
		}
		
	}
	for(int j=0; j<g->n;j++)
		printf("%d ", found_list[j]);
	
}
// 간선을 나타내는 구조체
typedef struct EdgeNode {
	int dest; // 목적지 정점
	int weight; // 가중치
	struct EdgeNode* next; // 다음 간선을 가리키는 포인터
} EdgeNode;

// 인접 리스트 방식 그래프
typedef struct GraphType1 {
	int n; // 정점의 개수
	EdgeNode* adj_list[MAX_VERTICES]; // 각 정점의 인접 리스트를 나타내는 배열
} List_GraphType;

void list_shortest_path(List_GraphType* g, int start) {
	printf("인접 리스트 방식\n");
	int i, u, w;
	for (i = 0; i < g->n; i++) {
		distance[i] = INF;
		found[i] = FALSE;
	}
	distance[start] = 0;


	for (i = 0; i < g->n; i++) {

		u = choose(distance, g->n, found);

		EdgeNode* current = g->adj_list[u];
		while (current != NULL) {
			w = current->dest;
			if (!found[w] && (distance[u] + current->weight < distance[w])) {
				distance[w] = distance[u] + current->weight;
			}
			current = current->next;
		}
		found[u] = TRUE;
		found_list1[j1] = u + 1;
		j1++;
		print_status(g);
	}

	for (int j = 0; j < g->n; j++)
		printf("%d ", found_list1[j]);
}

// 그래프 초기화 함수
void init_graph(List_GraphType* g, int n) {
	g->n = n;
	for (int i = 0; i < n; i++) {
		g->adj_list[i] = NULL;
	}
}

// 간선 추가 함수
void add_edge(List_GraphType* g, int start, int end, int weight) {
	EdgeNode* new_node = (EdgeNode*)malloc(sizeof(EdgeNode));
	new_node->dest = end;
	new_node->weight = weight;
	new_node->next = g->adj_list[start];
	g->adj_list[start] = new_node;
}


int main(void)
{
	
	//그래프 그리기
	Mat_GraphType g = { 10,
	{{ 0, 3, INF, INF, INF, 11, 12, INF, INF, INF },
	{ 3, 0, 5, 4, 1, 7, 8, INF, INF, INF},
	{ INF, 5, 0, 2, INF, INF, 6, 5, INF, INF },
	{ INF, 4, 2, 0, 13, INF, INF, 14, INF, 16 },
	{ INF, 1, INF, 13, 0, 9, INF, INF, 18, 17 },
	{ 11, 7, INF, INF, 9, 0, INF, INF, INF, INF },
	{ 12, 8, 6, INF, INF, INF, 0, 13, INF, INF },
	{ INF, INF, 5, 14, INF, INF, 13, 0, INF, 15},
	{ INF, INF, INF, INF, 18, INF, INF,INF, 0, 10},
	{ INF, INF, INF, 16, INF, INF, INF, 15, 10, 0}} };
	//shortest_path(&g, 0);
	
	List_GraphType g1;
	init_graph(&g1, 10);

	// 간선 추가
	add_edge(&g1, 0, 1, 3);
	add_edge(&g1, 0, 5, 11);
	add_edge(&g1, 0, 6, 12);
	add_edge(&g1, 1, 2, 5);
	add_edge(&g1, 1, 3, 4);
	add_edge(&g1, 1, 4, 1);
	add_edge(&g1, 1, 5, 7);
	add_edge(&g1, 1, 6, 8);
	add_edge(&g1, 2, 3, 2);
	add_edge(&g1, 2, 6, 6);
	add_edge(&g1, 2, 7, 5);
	add_edge(&g1, 3, 4, 13);
	add_edge(&g1, 3, 7, 14);
	add_edge(&g1, 3, 9, 16);
	add_edge(&g1, 4, 5, 9);
	add_edge(&g1, 4, 8, 18);
	add_edge(&g1, 4, 9, 17);
	add_edge(&g1, 6, 7, 13);
	add_edge(&g1, 7, 9, 15);
	add_edge(&g1, 8, 9, 10);

	list_shortest_path(&g1, 0);
	
	return 0;
}


