//[?] ������ �迭 ����� ���ÿ� �ʱ�ȭ
#include <stdio.h>

int main(void)
{
    // 2���� �迭 ����� ���ÿ� �ʱ�ȭ 
    int intArray[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };

    // 2�� for ������ 2���� �迭 ���
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d\t", intArray[i][j]);
        }
        printf("\n"); // �� ��� �� �ٹٲ�
    }

    return 0;
}
