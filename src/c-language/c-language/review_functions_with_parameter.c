#include <stdio.h>

// �Լ� ����: ������ �Ű������� ����
void printNumber(int num);

// �Լ� ����: �� ���� ������ �Ű������� �޾� ���� ���
void printSum(int a, int b);

int main(void)
{
    printNumber(5);  // ���� 5�� �����Ͽ� �Լ� ȣ��
    printNumber(10);  // ���� 10�� �����Ͽ� �Լ� ȣ��

    printSum(3, 7);  // ���� 3�� 7�� �����Ͽ� ���� ���
    printSum(10, 20);  // ���� 10�� 20�� �����Ͽ� ���� ���

    return 0;
}

// �Լ� ����: ���޹��� ������ ���
void printNumber(int num)
{
    printf("���޹��� ����: %d\n", num);
}

// �Լ� ����: ���޹��� �� ������ ���� ���
void printSum(int a, int b)
{
    int sum = a + b;
    printf("�� ���� ��: %d\n", sum);
}