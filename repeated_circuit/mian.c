#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
    int n;                        // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];  // 그래프의 가중치를 나타내는 인접 행렬
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];  // 최단 경로를 저장하는 행렬
int distance[MAX_VERTICES];
int found[MAX_VERTICES];

// 최소값 선택 함수
int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INF;
    minpos = -1;

    // distance 배열에서 최소값을 찾아 반환하는 함수
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 최단 경로 출력 함수
void printPath(int path[], int start, int end) {
    // 출발 노드와 도착 노드가 동일한 경우
    if (start == end) {
        printf("%d ", start + 1);
    }
    // 최단 경로 상에 노드(end)가 존재하지 않는 경우
    else if (path[end] == -1) {
        printf("%d %d ", start + 1, end + 1);
    }
    // 최단 경로가 존재하는 경우
    else {
        // 시작 노드부터 현재 노드(end)까지의 최단 경로 출력
        printPath(path, start, path[end]);
        // 현재 노드(end) 출력
        printf("%d ", end + 1);
    }
}


//최소 거리 구하기
void shortest_path(GraphType* g, int start, int end) {
    int i, u, w;
    int j = 0;

    // path 배열 초기화
    int path[MAX_VERTICES];
    for (i = 0; i < g->n; i++) {
        path[i] = -1;  // -1은 아직 최단 경로가 발견되지 않았음을 나타냄
    }

    for (i = 0; i < g->n; i++) { // 초기화
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }

    found[start] = TRUE;    // 시작 정점 방문 표시
    distance[start] = 0;      // 시작 정점 거리 0

    while (!found[end]) {  // 끝점이 방문되지 않았을 때까지 반복
        u = choose(distance, g->n, found); // min값 확인

        found[u] = TRUE;  // 최소거리 정점 방문표시
        for (w = 0; w < g->n; w++) {  // 최소거리 업데이트를 하기위한 반복
            if (!found[w]) {  // 방문하지 않았고
                if (distance[u] + g->weight[u][w] < distance[w]) { // 새로 찾은 거리가 현재 최소거리보다 작은 경우
                    distance[w] = distance[u] + g->weight[u][w]; // 최소거리 업데이트
                    path[w] = u;  // w까지의 최단 경로에서 u를 거쳐가는 것으로 업데이트
                }
            }
        }
    }

    // 최단 경로 출력
    printPath(path, start, end);
}

// Floyd-Warshall 알고리즘을 수행하는 함수
void floyd(GraphType* g) {
    int i, j, k;

    // 초기화: 인접 행렬의 값으로 초기화
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            A[i][j] = g->weight[i][j];

    // Floyd-Warshall 알고리즘
    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++)
            for (j = 0; j < g->n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
    }
}

int main(void) {
    // 그래프 그리기
    GraphType g = { 10,
    {{0, 3, INF, INF, INF, 11, 12, INF, INF, INF},
    {3, 0, 5, 4, 1, 7, 8, INF, INF, INF},
    {INF, 5, 0, 2, INF, INF, 6, 5, INF, INF},
    {INF, 4, 2, 0, 13, INF, INF, 14, INF, 16},
    {INF, 1, INF, 13, 0, 9, INF, INF, 18, 17},
    {11, 7, INF, INF, 9, 0, INF, INF, INF, INF},
    {12, 8, 6, INF, INF, INF, 0, 13, INF, INF},
    {INF, INF, 5, 14, INF, INF, 13, 0, INF, 15},
    {INF, INF, INF, INF, 18, INF, INF, INF, 0, 10},
    {INF, INF, INF, 16, INF, INF, INF, 15, 10, 0}} };

    floyd(&g);

    printf("Floyd-Warshall Algorithm\n");

    while (1) {
        int start, end;
       
        // 사용자로부터 출발 노드와 도착 노드를 입력받음
        printf("Start Node: ");
        scanf_s("%d", &start);
        printf("End Node: ");
        scanf_s("%d", &end);

        // 최단 거리 출력
        printf("Shortest Distance: %d\n", A[start - 1][end - 1]);
        shortest_path(&g, start - 1, end - 1);
        printf("\n\n");
    }

    return 0;
}
