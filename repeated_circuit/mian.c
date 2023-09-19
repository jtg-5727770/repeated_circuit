#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	double data;
	struct TreeNode* left, * right;
} TreeNode;

//��ũ ��� ���Է�
TreeNode n1 = { 2, NULL, NULL };
TreeNode n2 = { 3, NULL, NULL };
TreeNode n3 = { '+', &n1, &n2 };
TreeNode n4 = { 4, NULL, NULL };
TreeNode n5 = { 5, NULL, NULL };
TreeNode n6 = { '*', &n4, &n5 };
TreeNode n7 = { '+', &n3, &n6 };
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
        printf("%.2lf %c %.2lf\n", op1, (char)root->data, op2);
        switch ((char)root->data) { //���
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/':
            if (op2 != 0) {
                return op1 / op2;
            }
            else {
                printf("������ ����\n");
                exit(1); 
            }
        }
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