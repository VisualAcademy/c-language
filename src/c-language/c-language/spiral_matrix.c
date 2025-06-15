#include <stdio.h>

#define N 5  // �迭 ũ�⸦ ������ Ÿ�� ����� ����

int main(void)
{
    // ���������� ���� ä�� 2���� �迭
    int arr[N][N];

    // ���� ä���� �� ����
    int num = 1;

    // ���� ���
    int top = 0;

    // �Ʒ��� ���
    int bottom = N - 1;

    // ���� ���
    int left = 0;

    // ������ ���
    int right = N - 1;

    // ���������� �迭 ä���
    while (top <= bottom && left <= right) // ���������� ���� ���� ������ ���� �ִ� ���� �ݺ�
    {
        // �� ���������� ä���
        for (int i = left; i <= right; i++)
        {
            arr[top][i] = num++;
        }
        top++;

        // �� �Ʒ������� ä���
        for (int i = top; i <= bottom; i++)
        {
            arr[i][right] = num++;
        }
        right--;

        // �� �������� ä���
        for (int i = right; i >= left; i--)
        {
            arr[bottom][i] = num++;
        }
        bottom--;

        // �� �������� ä���
        for (int i = bottom; i >= top; i--)
        {
            arr[i][left] = num++;
        }
        left++;
    }

    // ��� ���
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}