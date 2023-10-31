#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 11 // ���ð� ť�� �ִ� ũ��
typedef int element; // �������� �ڷ���
element stack[MAX_SIZE]; // 1���� �迭
int top = -1;

// ���� ���� ���� ���� �Լ�
int stack_is_empty()
{
	return (top == -1);
}
// ���� ��ȭ ���� ���� �Լ�
int stack_is_full()
{
	return (top == (MAX_SIZE - 1));
}
// ���� push �Լ�
void push(element item)
{
	if (stack_is_full()) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else stack[++top] = item;
}
// ���� pop �Լ�
element pop()
{
	if (stack_is_empty()) {
		fprintf(stderr, "���� ���� ����\n");
		return;
	}
	else return stack[top--];
}

typedef struct { // ť Ÿ��
	int front;
	int rear;
	element data[MAX_SIZE];
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1); // [juht] ���α׷� ����� ������ ���� ó��
}
//ť �ʰ�ȭ
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}
//ť ��ȭ ����
int queue_is_full(QueueType* q)
{
	if (q->rear == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}
//ť ���� ����
int queue_is_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}
//ť ����
void enqueue(QueueType* q, int item)
{
	if (queue_is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
		return; // [juht] �ǹ� ����
	}
	q->data[++(q->rear)] = item;
}
//ť ���� 
int dequeue(QueueType* q) // [juht] element dequeue(QueType *q)
{
	if (queue_is_empty(q)) {
		error("ť�� ��������Դϴ�.");
		return -1; // [juht] �ǹ� ����
	}
	int item = q->data[++(q->front)];
	return item;
}

#define MAX_VERTICES 50
typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
//�迭 bfs
int visited[MAX_VERTICES];
void bfs_mat(GraphType* g, int v)
{
	int w;
	QueueType q;

	init_queue(&q);     // ť �ʱ�ȭ 
	visited[v] = 1;          // ���� v �湮 ǥ�� 
	printf("%d ", v);
	enqueue(&q, v);			// ���� ������ ť�� ���� 
	while (!queue_is_empty(&q)) {
		v = dequeue(&q);		// ť�� ���� ���� 
		for (w = 0; w < g->n; w++)	// ���� ���� Ž�� 
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1;    // �湮 ǥ��
				printf("%d ", w);
				enqueue(&q, w); 	// �湮�� ������ ť�� ����
			}
	}
}

int main(void) {
	int n, n1, n2;
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 12; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 5);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 9);
	insert_edge(g, 0, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 1, 4);
	insert_edge(g, 1, 7);
	insert_edge(g, 1, 10);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 3, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 10);
	insert_edge(g, 8, 9);


	printf("=========�޴�=========\n");
	printf("1.���� �켱 Ž��\n");
	printf("2.�ʺ� �켱 Ž��\n");
	printf("3.���α׷� ����\n");

	while (1) {

		printf("\n��ȣ�� �����ϼ���: ");
		scanf_s("%d", &n);

		switch (n) {
		case 1:
			printf("���� ��ȣ�� Ž���� ���� �Է�: ");
			scanf_s("%d &d", &n1, &n2);
			break;

		case 2:
			printf("���� ��ȣ�� Ž���� ���� �Է�: ");
			scanf_s("%d &d", &n1, &n2);
			bfs_mat(g, 0);
			break;
		case 3:
			printf("���α׷��� �����մϴ�.\n");
			free(g);
			return 0;
		default:
			printf("�ٽ� �������ּ���.\n");
			while (getchar() != '\n');
		}
	}
	system("pause");
	return 0;
}