#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; //방문 표시
int distance[MAX_VERTICES]; //거리 표시

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { //방문하지 않았으면
			v = i;          //v에 i를 집어넣음
			break;
		}
	for (i = 0; i < n; i++)
		//방문하지 않았고 거리가 더 짧을 경우 더 짧은거리를 선택
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;  
	return (v);
}

//최소 비용 신장트리를 구하는 Prim의 알고리즘
void prim(GraphType* g, int s)
{
	int i, u, v;

	printf("Prim MST 알고리즘\n");
	for (u = 0; u < g->n; u++) // distance배열을 모드 INF로 초기화
		distance[u] = INF;
	distance[s] = 0; //시작하는 노드만 0으로 해서 시작점이라고 표시

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE; 
		if (distance[u] == INF) return;
		printf("정점 %d 추가\n", u+1);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF) //노드가 이어져 있는경우
				if (!selected[v] && g->weight[u][v] < distance[v]) 
					distance[v] = g->weight[u][v];
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
	prim(&g, 0);
	return 0;
}
