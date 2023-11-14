#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
    int n;                        // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];  // �׷����� ����ġ�� ��Ÿ���� ���� ���
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];  // �ִ� ��θ� �����ϴ� ���
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int list_A[MAX_VERTICES];
int j = 0;


// �ּҰ� ���� �Լ�
int choose(int distance[], int n, int found[],int j) {
    int i, min, minpos;
    min = INF;
    minpos = -1;

    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    list_A[j++] = minpos + 1;
    return minpos;
}

// �ּҰŸ� ���ϱ�
void shortest_path(GraphType* g, int start, int end) {
    int i, u, w;
    int j = 0;
    for (i = 0; i < g->n; i++) { // �ʱ�ȭ
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }

    found[start] = TRUE;    // ���� ���� �湮 ǥ��
    distance[start] = 0;      // ���� ���� �Ÿ� 0
    list_A[j++] = start + 1;

    while (!found[end]) {  // ������ �湮���� �ʾ��� ������ �ݺ�
        u = choose(distance, g->n, found,j); // min�� Ȯ��

        found[u] = TRUE;  // �ּҰŸ� ���� �湮ǥ��
        for (w = 0; w < g->n; w++) {  // �ּҰŸ� ������Ʈ�� �ϱ����� �ݺ�
            if (!found[w])  // �湮���� �ʾҰ�
                if (distance[u] + g->weight[u][w] < distance[w]) // ���� ã�� �Ÿ��� ���� �ּҰŸ����� ���� ���
                    distance[w] = distance[u] + g->weight[u][w]; // �ּҰŸ� ������Ʈ
        }
    }
    for (int j = 0; list_A[j] != 0; j++)
        printf("%d ", list_A[j]);
}

// Floyd-Warshall �˰����� �����ϴ� �Լ�
void floyd(GraphType* g) {
    int i, j, k;

    // �ʱ�ȭ: ���� ����� ������ �ʱ�ȭ
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            A[i][j] = g->weight[i][j];

    // Floyd-Warshall �˰���
    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++)
            for (j = 0; j < g->n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
    }
}

int main(void) {
    // �׷��� �׸���
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
        for (int i = 0; i < MAX_VERTICES; i++) {
            list_A[i] = 0;
        }
        // ����ڷκ��� ��� ���� ���� ��带 �Է¹���
        printf("Start Node: ");
        scanf_s("%d", &start);
        printf("End Node: ");
        scanf_s("%d", &end);

        // �ִ� �Ÿ� ���
        printf("Shortest Distance: %d\n", A[start - 1][end - 1]);
        shortest_path(&g, start - 1, end - 1);
        printf("\n\n");
    }

    return 0;
}
