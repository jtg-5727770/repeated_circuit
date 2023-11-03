#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // 스택과 큐의 최대 크기
typedef int element; // 데이터의 자료형
typedef struct {
	element data[MAX_SIZE];
	int top;
}StackType;

//스택 초기화
int init_stack(StackType* s)
{
	s->top = -1;
}

// 스택 공백 상태 검출 함수
int stack_is_empty(StackType* s)
{
	return (s->top == -1);
}
// 스택 포화 상태 검출 함수
int stack_is_full(StackType* s)
{
	return (s->top == (MAX_SIZE - 1));
}
// 스택 push 함수
void push(StackType* s, element item)
{
	if (stack_is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 스택 pop 함수
element pop(StackType* s)
{
	if (stack_is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return 0;
	}
	else return s->data[(s->top)--];
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
int count;
//배열 bfs
int visited[MAX_VERTICES];
void bfs_mat(GraphType* g, int v, int target) {
	int w;
	QueueType q;

	init_queue(&q);     // 큐 초기화 
	visited[v] = 1;     // 정점 v 방문 표시 
	enqueue(&q, v);     // 시작 정점을 큐에 저장 
	printf("%d ", v);
	while (!queue_is_empty(&q)) {
		v = dequeue(&q); // 큐에서 정점 추출 

		if (v == target) {
			// 찾은 경우 탐색 중지
			printf("\n탐색성공: %d\n", target);
			return;
		}

		for (w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				if (w == target) {
					// 찾은 경우 탐색 중지
					printf("%d ", w);
					count++;
					printf("\n탐색성공: %d\n", target);
					return;
				}
				visited[w] = 1;    // 방문 표시
				printf("%d ", w);
				count++;
				enqueue(&q, w);  // 방문한 정점을 큐에 저장
			}
		}
	}

	// 목표 값을 찾지 못한 경우
	printf("\n%d를 찾지 못했습니다.\n", target);

}

//배열 dfs
void dfs_mat(GraphType* g, int v, int target) {
	StackType stack;
	init_stack(&stack); // 스택 초기화

	push(&stack, v); // 시작 노드를 스택에 넣음
	visited[v] = 1; // 시작 노드를 방문 표시
	printf("%d ", v); // 시작 노드를 출력

	while (!stack_is_empty(&stack)) {
		int current = stack.data[stack.top]; // 스택의 맨 위 노드를 가져옴
		int found = 0; // 연결된 미방문 노드를 찾았는지 여부

		if (current == target) {
			printf("\n탐색 성공: %d\n", target);
			return; // 목표 노드를 찾았으면 종료
		}

		for (int w = 0; w < g->n; w++) {
			if (g->adj_mat[current][w] && !visited[w]) {
				found = 1; // 연결된 미방문 노드 발견
				visited[w] = 1; // 노드를 방문 표시
				printf("%d ", w); // 노드를 출력
				push(&stack, w); // 스택에 노드를 넣음
				count++;
				break; // 첫 번째 미방문 노드만 스택에 넣고 이동
			}
		}

		//연결된 노드중 미방문 모드가 없으면
		if (!found) {
			pop(&stack); //마지막에 푸시한 값이 중복출력되는걸 방지하기위해 하나를 빼준다
			while (!stack_is_empty(&stack)) { // 하나씩 pop하기
				int popped = pop(&stack);
				count++;
				printf("%d ", popped);

				int shouldBreak = 0; //브레이크를 위한 변수
				int current1 = stack.data[stack.top];
				for (int w = 0; w < g->n; w++) { //pop한 노드에서 이어진 노드중 방문안한 노드 찾기
					if (g->adj_mat[current1][w] && !visited[w]) {
						shouldBreak = 1; //방문안한 노드 찾음
						break;
					}
				}
				//방문안한 노드를 찾았으면 하나를 더 pop하고 while문 종료
				if (shouldBreak == 1) { 
					int popped1 = pop(&stack);
					count++;
					printf("%d ", popped1);
					break; 
				}
			}
		}

	}

	printf("\n%d를 찾지 못했습니다.\n", target);
	
}

//모든 노드의 visited를 0으로 초기화
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
			scanf_s("%d %d", &n1, &n2);
			count = 0;
			dfs_mat(g, n1, n2);
			printf("방문한 횟수: %d\n", count);
			reset_visited(visited, g->n);
			break;

		case 2:
			printf("시작 번호와 탐색할 값을 입력: ");
			scanf_s("%d %d", &n1, &n2);
			count = 0;
			bfs_mat(g, n1, n2);
			printf("방문한 횟수: %d\n", count);
			reset_visited(visited, g->n);
			break;
		case 3:
			printf("프로그램을 종료합니다.\n");
			free(g);
			return 0;
		default:
			printf("다시 선택해주세요.\n");
		}
	}
	system("pause");
	return 0;
}