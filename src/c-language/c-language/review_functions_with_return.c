#include <stdio.h>

// �Լ� ����: ������ �Ű������� �޾� �������� ��ȯ
int square(int num);

int main(void)
{
    int result = square(4);  // ���� 4�� �������� �Լ��κ��� ��ȯ����
    printf("4�� ����: %d\n", result);

    printf("7�� ����: %d\n", square(7));  // ��ȯ���� �ٷ� ���
    return 0;
}

// �Լ� ����: ���޹��� ������ ������ ��ȯ
int square(int num)
{
    return num * num;
}