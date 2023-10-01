#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 이진 트리 노드 구조체 정의
typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// 반복적인 탐색 함수
TreeNode* search(TreeNode* node, int key, int* count)
{
    while (node != NULL) {
        (*count)++; // 방문한 노드 수 증가
        if (key == node->key) {
            return node; // 노드 객체 반환 (키 일치)
        }
        else if (key < node->key) {
            node = node->left; // 키가 더 작으면 왼쪽 서브트리로 이동
        }
        else {
            node = node->right; // 키가 더 크면 오른쪽 서브트리로 이동
        }
    }
    return NULL; // 탐색에 실패했을 경우 NULL 반환
}

// 새로운 노드 생성
TreeNode* new_node(int item)
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 삽입함수(재귀)
int insert_count = 0; // 노드 삽입시 방문한 노드 수를 저장하는 변수

TreeNode* insert_node1(TreeNode* node, int key)
{
    if (node == NULL) {
        return new_node(key); // 빈 트리인 경우 새로운 노드를 반환
    }

    // 그렇지 않으면 순환적으로 트리를 내려감
    if (key < node->key) {
        insert_count++; // 노드를 지나갈 때마다 방문한 노드 수 증가
        node->left = insert_node1(node->left, key);
    }
    else if (key > node->key) {
        insert_count++; // 노드를 지나갈 때마다 방문한 노드 수 증가
        node->right = insert_node1(node->right, key);
    }
    // 변경된 루트 포인터를 반환
    return node;
}

// 가장 작은 값을 가진 노드 반환
TreeNode* min_value_node(TreeNode* node)
{
    TreeNode* current = node;

    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL)
        current = current->left;

    return current;
}

// 삭제함수(재귀)
int delete_count = 0; // 방문한 노드 수를 저장하는 변수

TreeNode* delete_node1(TreeNode* root, int key)
{
    if (root == NULL) return root;

    // 만약 키가 루트보다 작으면 왼쪽 서브트리에 있는 것임
    if (key < root->key)
        root->left = delete_node1(root->left, key);
    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if (key > root->key)
        root->right = delete_node1(root->right, key);
    // 키가 루트와 같으면 이 노드를 삭제하면 됨
    else {
        // 첫 번째나 두 번째 경우
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // 세 번째 경우
        TreeNode* temp = min_value_node(root->right);

        // 중위 순회시 후계 노드를 복사한다.
        root->key = temp->key;
        // 중위 순회시 후계 노드를 삭제한다.
        root->right = delete_node1(root->right, temp->key);
    }
    return root;
}

// 삽입함수(반복)
TreeNode* insert_node2(TreeNode* node, int key)
{
    if (node == NULL) {
        return new_node(key); // 빈 트리인 경우 새로운 노드를 반환
    }

    TreeNode* current = node;

    while (1) {
        if (key < current->key) {
            insert_count++;
            if (current->left == NULL) {
                current->left = new_node(key);
                break;
            }
            current = current->left;
        }
        else if (key > current->key) {
            insert_count++;
            if (current->right == NULL) {
                current->right = new_node(key);
                break;
            }
            current = current->right;
        }
        else {
            break; // 이미 같은 키의 노드가 있을 때 루프 종료
        }
    }

    return node;
}

// 삭제함수(반복)
TreeNode* delete_node2(TreeNode* node, int key)
{
    TreeNode* current = node; // 현재 노드를 가리킬 포인터
    TreeNode* parent = NULL;  // 삭제 대상 노드의 부모 노드를 가리킬 포인터

    while (current != NULL) {
        if (key == current->key) {
            // 삭제 대상 노드를 찾음
            if (current->left == NULL && current->right == NULL) {
                // 삭제 대상 노드가 단말 노드인 경우
                if (parent == NULL) {
                    // 삭제 대상 노드가 루트 노드인 경우
                    free(current);
                    return NULL;
                }
                if (parent->left == current) {
                    free(current);
                    parent->left = NULL;
                }
                else {
                    free(current);
                    parent->right = NULL;
                }
            }
            else if (current->left != NULL && current->right != NULL) {
                // 삭제 대상 노드가 두 개의 자식을 가진 경우
                TreeNode* min_right = min_value_node(current->right);
                current->key = min_right->key;
                key = min_right->key;
                parent = current;
                current = current->right;
            }
            else {
                // 삭제 대상 노드가 하나의 자식을 가진 경우
                TreeNode* child = (current->left != NULL) ? current->left : current->right;
                if (parent == NULL) {
                    // 삭제 대상 노드가 루트 노드인 경우
                    free(current);
                    return child;
                }
                if (parent->left == current) {
                    free(current);
                    parent->left = child;
                }
                else {
                    free(current);
                    parent->right = child;
                }
            }
            return node;
        }
        else if (key < current->key) {
            parent = current;
            current = current->left;
        }
        else {
            parent = current;
            current = current->right;
        }
    }
    // 삭제 대상 노드를 찾지 못한 경우 루트 노드를 그대로 반환
    return node;
}

// 중위 순회 함수 (트리의 노드 값을 중위 순서로 출력)
int inorder_count = 0;
void inorder(TreeNode* root) {

    if (root) {
        inorder_count++;
        inorder(root->left);   // 왼쪽 서브트리 순회
        printf("%d ", root->key);  // 노드 방문
        inorder(root->right);  // 오른쪽 서브트리 순회
    }
}

int main()
{
    TreeNode* root = NULL;

    // 노드 값 입력
    root = insert_node1(root, 60);
    root = insert_node1(root, 41);
    root = insert_node1(root, 16);
    root = insert_node1(root, 25);
    root = insert_node1(root, 53);
    root = insert_node1(root, 46);
    root = insert_node1(root, 42);
    root = insert_node1(root, 55);
    root = insert_node1(root, 74);
    root = insert_node1(root, 65);
    root = insert_node1(root, 63);
    root = insert_node1(root, 62);
    root = insert_node1(root, 64);
    root = insert_node1(root, 70);

    int k;

    char input[100];
    while (1) {
        printf("=========메뉴=========\n");
        printf("s) 검색\n");
        printf("i) 노드 추가\n");
        printf("d) 노드 삭제\n");
        printf("t) 중위 순회\n");
        printf("l) 노드 추가(반복)\n");
        printf("D) 노드삭제(반복)\n");
        printf("c) 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf_s("%s", input, sizeof(input));
        if (strlen(input) == 1) {
            char c = input[0];

            switch (c) {
            case 's':
                printf("검색할 값 입력: ");
                scanf_s("%d", &k);
                int search_count = 0; // 방문한 노드 수를 저장할 변수
                TreeNode* result = search(root, k, &search_count);
                if (result != NULL) {
                    printf("검색 성공: %d\n", k);
                    printf("방문한 노드의 수: %d\n", search_count);
                }
                else
                    printf("검색 실패: %d\n", k);
                inorder(root);
                printf("\n\n");
                break;

            case 'i':
                printf("삽입할 값 입력: ");
                scanf_s("%d", &k);
                insert_count = 0;
                root = insert_node1(root, k);
                printf("방문한 노드의 수: %d\n", insert_count); // 방문한 노드 수 출력
                inorder(root);
                printf("\n\n");

                break;

            case 'd':
                printf("삭제할 값 입력: ");
                scanf_s("%d", &k);
                delete_count = 0;
                TreeNode* delete_result1 = search(root, k, &delete_count);
                root = delete_node1(root, k);
                if (delete_result1 != NULL) {
                    printf("방문한 노드의 수: %d\n", delete_count);
                }
                inorder(root);
                printf("\n\n");
                break;

            case 't':
                printf("중위 순회\n"); 
                inorder_count = 0;
                inorder(root);
                printf("\n");
                printf("방문한 노드의 수: %d", inorder_count);
                printf("\n\n");
                break;

            case 'I':
                printf("삽입할 값 입력: ");
                scanf_s("%d", &k);
                insert_count = 0;
                root = insert_node2(root, k);
                printf("방문한 노드의 수: %d\n", insert_count); // 방문한 노드 수 출력
                inorder(root);
                printf("\n\n");
                break;

            case 'D':
                printf("삭제할 값 입력: ");
                scanf_s("%d", &k);
                delete_count = 0; // 방문한 노드 수를 저장할 변수
                TreeNode* delete_result2 = search(root, k, &delete_count);
                root = delete_node2(root, k);
                if (delete_result2 != NULL) {
                    printf("방문한 노드의 수: %d\n", delete_count);
                }
                inorder(root);
                printf("\n\n");
                break;

            case 'c':
                printf("프로그램을 종료합니다.\n");
                exit(0);
            default:
                printf("다시 선택해주세요.\n");
                while (getchar() != '\n');
            }
        }
        else {
            printf("다시 선택해주세요.\n");

        }

    }
    return 0;
}