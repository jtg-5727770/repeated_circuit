
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100	
#define INF	1000000	//���Ѵ� (������ ���� ���) 


int distance[MAX_VERTICES]; // �����������κ����� �ִܰ�� �Ÿ� 
int found[MAX_VERTICES];		// �湮�� ���� ǥ�� 
int found_list[MAX_VERTICES];  // Ž�� ���� ������ ������ ����Ʈ
int found_list1[MAX_VERTICES];
int j = 0;
int j1 = 0;
// ���� �迭��� �׷���
typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} Mat_GraphType;

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
	found_list[j] = minpos + 1;
	j++;
	return minpos; // �ִ� �Ÿ��� ���� ������ �ε��� ��ȯ
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

// �ּҰŸ� ���ϱ�
void shortest_path(Mat_GraphType* g, int start)
{
	printf("���� �迭 ���\n");
	int i, u, w;
	for (i = 0; i < g->n; i++) // �ʱ�ȭ 
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		
	}
	found[start] = TRUE;    // ���� ���� �湮 ǥ�� 
	distance[start] = 0;      // ���� ���� �Ÿ� 0
	found_list[j] = start + 1;
	j++;
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
	for(int j=0; j<g->n;j++)
		printf("%d ", found_list[j]);
	
}
// ������ ��Ÿ���� ����ü
typedef struct EdgeNode {
	int dest; // ������ ����
	int weight; // ����ġ
	struct EdgeNode* next; // ���� ������ ����Ű�� ������
} EdgeNode;

// ���� ����Ʈ ��� �׷���
typedef struct GraphType1 {
	int n; // ������ ����
	EdgeNode* adj_list[MAX_VERTICES]; // �� ������ ���� ����Ʈ�� ��Ÿ���� �迭
} List_GraphType;

void list_shortest_path(List_GraphType* g, int start) {
	printf("���� ����Ʈ ���\n");
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

// �׷��� �ʱ�ȭ �Լ�
void init_graph(List_GraphType* g, int n) {
	g->n = n;
	for (int i = 0; i < n; i++) {
		g->adj_list[i] = NULL;
	}
}

// ���� �߰� �Լ�
void add_edge(List_GraphType* g, int start, int end, int weight) {
	EdgeNode* new_node = (EdgeNode*)malloc(sizeof(EdgeNode));
	new_node->dest = end;
	new_node->weight = weight;
	new_node->next = g->adj_list[start];
	g->adj_list[start] = new_node;
}


int main(void)
{
	
	//�׷��� �׸���
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

	// ���� �߰�
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


