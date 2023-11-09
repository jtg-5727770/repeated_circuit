#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */
int fouud_list[MAX_VERTICES];  // 탐색 성공 순서를 저장할 리스트


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
	return minpos;
}
void print_status(GraphType* g) {
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
void shortest_path(GraphType* g, int start)
{
	printf("인접 배열 방식\n");
	int i, u, w;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;      // 시작 정점 거리 0

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

}

int main(void)
{
	//그래프 그리기
	GraphType g = { 10,
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
	shortest_path(&g, 0);
	return 0;
}
