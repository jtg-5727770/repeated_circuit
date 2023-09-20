#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	double data;
	struct TreeNode* left, * right;
} TreeNode;

//��ũ ��� ���Է�
TreeNode n1 = { 4, NULL, NULL };
TreeNode n2 = { 5, NULL, NULL };
TreeNode n3 = { '*', &n1, &n2 };
TreeNode n4 = { 3, NULL, NULL };
TreeNode n5 = { '+', &n4, &n3};
TreeNode n6 = { 2, NULL, NULL };
TreeNode n7 = { '+', &n6, &n5 };
TreeNode n8 = { 6, NULL, NULL };
TreeNode n9 = { 7, NULL, NULL };
TreeNode n10 = { '/', &n8, &n9};
TreeNode n11 = { '-', &n7, &n10 }; 
TreeNode n12 = { 9, NULL, NULL };
TreeNode n13 = { '+', &n11, &n12 };
TreeNode* exp = &n13;

// ���� ��� �Լ�
double evaluate(TreeNode* root)
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return root->data;
    else {
        double op1 = evaluate(root->left);
        double op2 = evaluate(root->right);

        //���
        double result;

        switch ((char)root->data) {
        case '+':
            result = op1 + op2;
            break;
        case '-':
            result = op1 - op2;
            break;
        case '*':
            result = op1 * op2;
            break;
        case '/':
            if (op2 != 0) {
                result = op1 / op2;
            }
            else {
                printf("������ ����\n");
                exit(1);
            }
            break;
        }

        printf("%.2lf %c %.2lf = %.2lf\n", op1, (char)root->data, op2, result);
        return result;
    }
    return 0;
}

// ��� ���� ī��Ʈ 
int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;	
}

void  main()
{
	printf("������ ���� %.2lf�Դϴ�. \n\n", evaluate(exp));
	printf("�� ����� ���� %d���Դϴ�.\n", get_node_count(exp));
	return 0;
}