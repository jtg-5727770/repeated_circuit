#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 11 // 스택과 큐의 최대 크기
typedef int element; // 데이터의 자료형
element stack[MAX_SIZE]; // 1차원 배열
int top = -1;

// 스택 공백 상태 검출 함수
int stack_is_empty()
{
	return (top == -1);
}
// 스택 포화 상태 검출 함수
int stack_is_full()
{
	return (top == (MAX_SIZE - 1));
}
// 스택 push 함수
void push(element item)
{
	if (stack_is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;
}
// 스택 pop 함수
element pop()
{
	if (stack_is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		return;
	}
	else return stack[top--];
}

typedef struct { // 큐 타입
	int front;
	int rear;
	element data[MAX_SIZE];
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1); // [juht] 프로그램 종료는 과도한 에러 처리
}
//큐 초가화
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}
//큐 포화 상태
int queue_is_full(QueueType* q)
{
	if (q->rear == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}
//큐 공백 상태
int queue_is_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}
//큐 삽입
void enqueue(QueueType* q, int item)
{
	if (queue_is_full(q)) {
		error("큐가 포화상태입니다.");
		return; // [juht] 의미 없음
	}
	q->data[++(q->rear)] = item;
}
//큐 삭제 
int dequeue(QueueType* q) // [juht] element dequeue(QueType *q)
{
	if (queue_is_empty(q)) {
		error("큐가 공백상태입니다.");
		return -1; // [juht] 의미 없음
	}
	int item = q->data[++(q->front)];
	return item;
}

#define MAX_VERTICES 50
typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
//배열 bfs
int visited[MAX_VERTICES];
void bfs_mat(GraphType* g, int v)
{
	int w;
	QueueType q;

	init_queue(&q);     // 큐 초기화 
	visited[v] = 1;          // 정점 v 방문 표시 
	printf("%d ", v);
	enqueue(&q, v);			// 시작 정점을 큐에 저장 
	while (!queue_is_empty(&q)) {
		v = dequeue(&q);		// 큐에 정점 추출 
		for (w = 0; w < g->n; w++)	// 인접 정점 탐색 
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1;    // 방문 표시
				printf("%d ", w);
				enqueue(&q, w); 	// 방문한 정점을 큐에 저장
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


	printf("=========메뉴=========\n");
	printf("1.깊이 우선 탐색\n");
	printf("2.너비 우선 탐색\n");
	printf("3.프로그램 종료\n");

	while (1) {

		printf("\n번호를 선택하세요: ");
		scanf_s("%d", &n);

		switch (n) {
		case 1:
			printf("시작 번호와 탐색할 값을 입력: ");
			scanf_s("%d &d", &n1, &n2);
			break;

		case 2:
			printf("시작 번호와 탐색할 값을 입력: ");
			scanf_s("%d &d", &n1, &n2);
			bfs_mat(g, 0);
			break;
		case 3:
			printf("프로그램을 종료합니다.\n");
			free(g);
			return 0;
		default:
			printf("다시 선택해주세요.\n");
			while (getchar() != '\n');
		}
	}
	system("pause");
	return 0;
}