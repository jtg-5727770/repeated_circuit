#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_SIZE 20

double move_count = 0;     // �̵�Ƚ�� ī��Ʈ
double compare_count = 0;  // ��Ƚ�� ī��Ʈ
int n1;

typedef struct {
    int left;
    int right;
} StackItem;

void push(StackItem stack[], int* top, int left, int right) {
    stack[++(*top)].left = left;
    stack[(*top)].right = right;
}

void pop(int* top) {
    (*top)--;
}
//����
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];

    do {
        do {
            low++;
            compare_count++;
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            compare_count++;
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
            move_count++;
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);
    move_count++;
    if (n1 == 0) {
        for (int i = 0; i < 20; i++) {
            printf("%d ", list[i]);

        }
        printf("\n");
    }
    return high;
}
//���
void quick_sort1(int list[], int left, int right)
{
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort1(list, left, q - 1);
        quick_sort1(list, q + 1, right);
    }
}
//�ݺ�
void quick_sort2(int list[], int left, int right) {
    int top = -1;
    StackItem stack[MAX_SIZE];
    push(stack, &top, left, right);

    while (top != -1) {
        left = stack[top].left;
        right = stack[top].right;
        pop(&top);

        int q = partition(list, left, right);

        if (left < q - 1) {
            push(stack, &top, left, q - 1);
        }

        if (q + 1 < right) {
            push(stack, &top, q + 1, right);
        }
    }
}

int main() {
    srand(time(NULL)); // ���� �ʱ�ȭ
    int n = MAX_SIZE;

    for (n1 = 0; n1 < 20; n1++) {
        int list_O[20];
        int random = 0;

        for (int i = 0; i < 20; i++) {
            random = rand() % 100;
            list_O[i] = random;
        }

        if (n1 == 0) {
            printf("�ʱ� ����Ʈ\n");
            for (int i = 0; i < 20; i++) {
                printf("%d ", list_O[i]);
            }
            printf("\n\n�� ����\n");
        }
        //���
        //quick_sort1(list_O, 0, n - 1);
        //�ݺ�
        quick_sort2(list_O, 0, n - 1);
    }

    printf("\n�̵� Ƚ�� ���: %f\n", move_count / 20);
    printf("�� Ƚ�� ���: %f", compare_count / 20);

    return 0;
}
