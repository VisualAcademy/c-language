#include <stdio.h>

int main(void)
{
    int numbers[] = { 10, 20, 30, 40, 50 };  // ������ �迭 ���� �� �ʱ�ȭ

    // �迭 ��Ҹ� �ϳ��� ���
    for (int i = 0; i < 5; i++)
    {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    return 0;
}