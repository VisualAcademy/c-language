//[?] ������ �迭 ���� �� �ݺ������� ����ϱ�
#include <stdio.h>

int main(void)
{
    // 2���� �迭 ����
    int intArray[2][3];

    // 2���� �迭 �ʱ�ȭ 
    intArray[0][0] = 1;
    intArray[0][1] = 2;
    intArray[0][2] = 3;

    intArray[1][0] = 4;
    intArray[1][1] = 5;
    intArray[1][2] = 6;

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
