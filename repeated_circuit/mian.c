#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; //�湮 ǥ��
int distance[MAX_VERTICES]; //�Ÿ� ǥ��

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { //�湮���� �ʾ�����
			v = i;          //v�� i�� �������
			break;
		}
	for (i = 0; i < n; i++)
		//�湮���� �ʾҰ� �Ÿ��� �� ª�� ��� �� ª���Ÿ��� ����
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;
	return (v);
}

//�ּ� ��� ����Ʈ���� ���ϴ� Prim�� �˰���
void prim(GraphType* g, int s)
{
	int i, u, v;

	printf("Prim MST �˰���\n");
	for (u = 0; u < g->n; u++) // distance�迭�� ��� INF�� �ʱ�ȭ
		distance[u] = INF;
	distance[s] = 0; //�����ϴ� ������ 0���� �ؼ� �������̶�� ǥ��

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); //�ּҰŸ��� �������ִ� ���� �R��
		selected[u] = TRUE; //�ش� ������ �湮ǥ��	
		if (distance[u] == INF) return; //��� ������ �̾����ְų� �и��Ǿ��ִ� ���
		printf("���� %d �߰�\n", u + 1);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF) //������ �̾��� �ִ°��
				if (!selected[v] && g->weight[u][v] < distance[v]) //���� �湮���� �ʾҰ� �� ���� �Ÿ��ϰ��
					distance[v] = g->weight[u][v]; //�ּ� �Ÿ� ������Ʈ
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
	prim(&g, 0);
	return 0;
}
