#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int key;
    struct TreeNode* left, * right;
} TreeNode;

// �ݺ����� Ž�� �Լ�
TreeNode* search(TreeNode* node, int key, int* count)
{
    while (node != NULL) {
        (*count)++; // �湮�� ��� �� ����
        if (key == node->key) {
            return node; // ��� ��ü ��ȯ (Ű ��ġ)
        }
        else if (key < node->key) {
            node = node->left; // Ű�� �� ������ ���� ����Ʈ���� �̵�
        }
        else {
            node = node->right; // Ű�� �� ũ�� ������ ����Ʈ���� �̵�
        }
    }
    return NULL; // Ž���� �������� ��� NULL ��ȯ
}

// ���ο� ��� ����
TreeNode* new_node(int item)
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// �����Լ�(���)
int insert_count = 0; // ��� ���Խ� �湮�� ��� ���� �����ϴ� ����

TreeNode* insert_node1(TreeNode* node, int key)
{
    if (node == NULL) {
        return new_node(key); // �� Ʈ���� ��� ���ο� ��带 ��ȯ
    }

    // �׷��� ������ ��ȯ������ Ʈ���� ������
    if (key < node->key) {
        insert_count++; // ��带 ������ ������ �湮�� ��� �� ����
        node->left = insert_node1(node->left, key);
    }
    else if (key > node->key) {
        insert_count++; // ��带 ������ ������ �湮�� ��� �� ����
        node->right = insert_node1(node->right, key);
    }
    // ����� ��Ʈ �����͸� ��ȯ
    return node;
}

// ���� ���� ���� ���� ��� ��ȯ
TreeNode* min_value_node(TreeNode* node)
{
    TreeNode* current = node;

    // �� ���� �ܸ� ��带 ã���� ������
    while (current->left != NULL)
        current = current->left;

    return current;
}

// �����Լ�(���)
int delete_count = 0; // �湮�� ��� ���� �����ϴ� ����

TreeNode* delete_node1(TreeNode* root, int key)
{
    if (root == NULL) return root;

    // ���� Ű�� ��Ʈ���� ������ ���� ����Ʈ���� �ִ� ����
    if (key < root->key)
        root->left = delete_node1(root->left, key);
    // ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
    else if (key > root->key)
        root->right = delete_node1(root->right, key);
    // Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
    else {
        // ù ��°�� �� ��° ���
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
        // �� ��° ���
        TreeNode* temp = min_value_node(root->right);

        // ���� ��ȸ�� �İ� ��带 �����Ѵ�.
        root->key = temp->key;
        // ���� ��ȸ�� �İ� ��带 �����Ѵ�.
        root->right = delete_node1(root->right, temp->key);
    }
    return root;
}

// �����Լ�(�ݺ�)
TreeNode* insert_node2(TreeNode* node, int key)
{
    if (node == NULL) {
        return new_node(key); // �� Ʈ���� ��� ���ο� ��带 ��ȯ
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
            break; // �̹� ���� Ű�� ��尡 ���� �� ���� ����
        }
    }

    return node;
}

// �����Լ�(�ݺ�)
TreeNode* delete_node2(TreeNode* node, int key)
{
    TreeNode* current = node; // ���� ��带 ����ų ������
    TreeNode* parent = NULL;  // ���� ��� ����� �θ� ��带 ����ų ������

    while (current != NULL) {
        if (key == current->key) {
            // ���� ��� ��带 ã��
            if (current->left == NULL && current->right == NULL) {
                // ���� ��� ��尡 �ܸ� ����� ���
                if (parent == NULL) {
                    // ���� ��� ��尡 ��Ʈ ����� ���
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
                // ���� ��� ��尡 �� ���� �ڽ��� ���� ���
                TreeNode* min_right = min_value_node(current->right);
                current->key = min_right->key;
                key = min_right->key;
                parent = current;
                current = current->right;
            }
            else {
                // ���� ��� ��尡 �ϳ��� �ڽ��� ���� ���
                TreeNode* child = (current->left != NULL) ? current->left : current->right;
                if (parent == NULL) {
                    // ���� ��� ��尡 ��Ʈ ����� ���
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
    // ���� ��� ��带 ã�� ���� ��� ��Ʈ ��带 �״�� ��ȯ
    return node;
}

// ���� ��ȸ �Լ� (Ʈ���� ��� ���� ���� ������ ���)
int inorder_count = 0;
void inorder(TreeNode* root) {

    if (root) {
        inorder_count++;
        inorder(root->left);   // ���� ����Ʈ�� ��ȸ
        printf("%d ", root->key);  // ��� �湮
        inorder(root->right);  // ������ ����Ʈ�� ��ȸ
    }
}

int main()
{
    TreeNode* root = NULL;

    // ��� �� �Է�
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
        printf("=========�޴�=========\n");
        printf("s) �˻�\n");
        printf("i) ��� �߰�\n");
        printf("d) ��� ����\n");
        printf("t) ���� ��ȸ\n");
        printf("l) ��� �߰�(�ݺ�)\n");
        printf("D) ������(�ݺ�)\n");
        printf("c) ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf_s("%s", input, sizeof(input));
        if (strlen(input) == 1) {
            char c = input[0];

            switch (c) {
            case 's':
                printf("�˻��� �� �Է�: ");
                scanf_s("%d", &k);
                int search_count = 0; // �湮�� ��� ���� ������ ����
                TreeNode* result = search(root, k, &search_count);
                if (result != NULL) {
                    printf("�˻� ����: %d\n", k);
                    printf("�湮�� ����� ��: %d\n", search_count);
                }
                else
                    printf("�˻� ����: %d\n", k);
                inorder(root);
                printf("\n\n");
                break;

            case 'i':
                printf("������ �� �Է�: ");
                scanf_s("%d", &k);
                insert_count = 0;
                root = insert_node1(root, k);
                printf("�湮�� ����� ��: %d\n", insert_count); // �湮�� ��� �� ���
                inorder(root);
                printf("\n\n");

                break;

            case 'd':
                printf("������ �� �Է�: ");
                scanf_s("%d", &k);
                delete_count = 0;
                TreeNode* delete_result1 = search(root, k, &delete_count);
                root = delete_node1(root, k);
                if (delete_result1 != NULL) {
                    printf("�湮�� ����� ��: %d\n", delete_count);
                }
                inorder(root);
                printf("\n\n");
                break;

            case 't':
                printf("���� ��ȸ\n"); 
                inorder_count = 0;
                inorder(root);
                printf("\n");
                printf("�湮�� ����� ��: %d", inorder_count);
                printf("\n\n");
                break;

            case 'I':
                printf("������ �� �Է�: ");
                scanf_s("%d", &k);
                insert_count = 0;
                root = insert_node2(root, k);
                printf("�湮�� ����� ��: %d\n", insert_count); // �湮�� ��� �� ���
                inorder(root);
                printf("\n\n");
                break;

            case 'D':
                printf("������ �� �Է�: ");
                scanf_s("%d", &k);
                delete_count = 0; // �湮�� ��� ���� ������ ����
                TreeNode* delete_result2 = search(root, k, &delete_count);
                root = delete_node2(root, k);
                if (delete_result2 != NULL) {
                    printf("�湮�� ����� ��: %d\n", delete_count);
                }
                inorder(root);
                printf("\n\n");
                break;

            case 'c':
                printf("���α׷��� �����մϴ�.\n");
                exit(0);
            default:
                printf("�ٽ� �������ּ���.\n");
                while (getchar() != '\n');
            }
        }
        else {
            printf("�ٽ� �������ּ���.\n");

        }

    }
    return 0;
}