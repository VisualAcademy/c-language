#include <stdio.h>

int main(void)
{
    int num = 10;  // �˻��� ���� ����

    if (num > 0)  // ������� �˻�
    {
        printf("����Դϴ�.\n");
    }
    else if (num < 0)  // �������� �˻�
    {
        printf("�����Դϴ�.\n");
    }
    else  // 0�� ���
    {
        printf("0�Դϴ�.\n");
    }

    return 0;
}