#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // ���ð� ť�� �ִ� ũ��
typedef int element; // �������� �ڷ���
typedef struct {
	element data[MAX_SIZE];
	int top;
}StackType;

//���� �ʱ�ȭ
int init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� ���� �Լ�
int stack_is_empty(StackType* s)
{
	return (s->top == -1);
}
// ���� ��ȭ ���� ���� �Լ�
int stack_is_full(StackType* s)
{
	return (s->top == (MAX_SIZE - 1));
}
// ���� push �Լ�
void push(StackType* s, element item)
{
	if (stack_is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// ���� pop �Լ�
element pop(StackType* s)
{
	if (stack_is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		return 0;
	}
	else return s->data[(s->top)--];
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
int count;
//�迭 bfs
int visited[MAX_VERTICES];
void bfs_mat(GraphType* g, int v, int target) {
	int w;
	QueueType q;

	init_queue(&q);     // ť �ʱ�ȭ 
	visited[v] = 1;     // ���� v �湮 ǥ�� 
	enqueue(&q, v);     // ���� ������ ť�� ���� 
	printf("%d ", v);
	while (!queue_is_empty(&q)) {
		v = dequeue(&q); // ť���� ���� ���� 

		if (v == target) {
			// ã�� ��� Ž�� ����
			printf("\nŽ������: %d\n", target);
			return;
		}

		for (w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				if (w == target) {
					// ã�� ��� Ž�� ����
					printf("%d ", w);
					count++;
					printf("\nŽ������: %d\n", target);
					return;
				}
				visited[w] = 1;    // �湮 ǥ��
				printf("%d ", w);
				count++;
				enqueue(&q, w);  // �湮�� ������ ť�� ����
			}
		}
	}

	// ��ǥ ���� ã�� ���� ���
	printf("\n%d�� ã�� ���߽��ϴ�.\n", target);

}

//�迭 dfs
void dfs_mat(GraphType* g, int v, int target) {
	StackType stack;
	init_stack(&stack); // ���� �ʱ�ȭ

	push(&stack, v); // ���� ��带 ���ÿ� ����
	visited[v] = 1; // ���� ��带 �湮 ǥ��
	printf("%d ", v); // ���� ��带 ���

	while (!stack_is_empty(&stack)) {
		int current = stack.data[stack.top]; // ������ �� �� ��带 ������
		int found = 0; // ����� �̹湮 ��带 ã�Ҵ��� ����

		if (current == target) {
			printf("\nŽ�� ����: %d\n", target);
			return; // ��ǥ ��带 ã������ ����
		}

		for (int w = 0; w < g->n; w++) {
			if (g->adj_mat[current][w] && !visited[w]) {
				found = 1; // ����� �̹湮 ��� �߰�
				visited[w] = 1; // ��带 �湮 ǥ��
				printf("%d ", w); // ��带 ���
				push(&stack, w); // ���ÿ� ��带 ����
				count++;
				break; // ù ��° �̹湮 ��常 ���ÿ� �ְ� �̵�
			}
		}

		//����� ����� �̹湮 ��尡 ������
		if (!found) {
			pop(&stack); //�������� Ǫ���� ���� �ߺ���µǴ°� �����ϱ����� �ϳ��� ���ش�
			while (!stack_is_empty(&stack)) { // �ϳ��� pop�ϱ�
				int popped = pop(&stack);
				count++;
				printf("%d ", popped);

				int shouldBreak = 0; //�극��ũ�� ���� ����
				int current1 = stack.data[stack.top];
				for (int w = 0; w < g->n; w++) { //pop�� ��忡�� �̾��� ����� �湮���� ��� ã��
					if (g->adj_mat[current1][w] && !visited[w]) {
						shouldBreak = 1; //�湮���� ��� ã��
						break;
					}
				}
				//�湮���� ��带 ã������ �ϳ��� �� pop�ϰ� while�� ����
				if (shouldBreak == 1) { 
					int popped1 = pop(&stack);
					count++;
					printf("%d ", popped1);
					break; 
				}
			}
		}

	}

	printf("\n%d�� ã�� ���߽��ϴ�.\n", target);
	
}

//��� ����� visited�� 0���� �ʱ�ȭ
void reset_visited(int visited[], int n) {
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
}

int main(void) {
	int n, n1, n2;
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 12; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 2);
	insert_edge(g, 0, 4);
	insert_edge(g, 0, 5);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 9);
	insert_edge(g, 1, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 1, 7);
	insert_edge(g, 1, 10);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	insert_edge(g, 8, 10);


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
			scanf_s("%d %d", &n1, &n2);
			count = 0;
			dfs_mat(g, n1, n2);
			printf("�湮�� Ƚ��: %d\n", count);
			reset_visited(visited, g->n);
			break;

		case 2:
			printf("���� ��ȣ�� Ž���� ���� �Է�: ");
			scanf_s("%d %d", &n1, &n2);
			count = 0;
			bfs_mat(g, n1, n2);
			printf("�湮�� Ƚ��: %d\n", count);
			reset_visited(visited, g->n);
			break;
		case 3:
			printf("���α׷��� �����մϴ�.\n");
			free(g);
			return 0;
		default:
			printf("�ٽ� �������ּ���.\n");
		}
	}
	system("pause");
	return 0;
}