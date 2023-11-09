#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];		/* �湮�� ���� ǥ�� */
int fouud_list[MAX_VERTICES];  // Ž�� ���� ������ ������ ����Ʈ


// Ž���ϸ� min�� Ȯ��
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

// �ּҰŸ� ���ϱ�
void shortest_path(GraphType* g, int start)
{
	printf("���� �迭 ���\n");
	int i, u, w;
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		
	}
	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;      // ���� ���� �Ÿ� 0

	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found); // min�� Ȯ��

		found[u] = TRUE;  // �ּҰŸ� ���� �湮ǥ��
		for (w = 0; w < g->n; w++) {  //�ּҰŸ� ������Ʈ�� �ϱ����� �ݺ�
			if (!found[w])  // �湮���� �ʾҰ�
				if (distance[u] + g->weight[u][w] < distance[w]) // ���� ã�� �Ÿ��� �����ּҰŸ����� ������� 
					distance[w] = distance[u] + g->weight[u][w]; // �ּҰŸ� ������Ʈ
					
		}
		
	}

}

int main(void)
{
	//�׷��� �׸���
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
