#include <stdio.h>

int main(void)
{
    int a = 5;  // ù ��° ���� ����
    int b = 3;  // �� ��° ���� ����

    int sum = a + b;  // ����
    int diff = a - b;  // ����
    int product = a * b;  // ����
    int quotient = a / b;  // ������
    int remainder = a % b;  // ������ ����

    printf("��: %d\n", sum);
    printf("��: %d\n", diff);
    printf("��: %d\n", product);
    printf("��: %d\n", quotient);
    printf("������: %d\n", remainder);

    return 0;
}