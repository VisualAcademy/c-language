// C �� �̿��� �簢���� ���� ��� ���α׷�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    // ���� ����
    double width = 0.0;  // �غ�
    double height = 0.0; // ����
    double area = 0.0;   // ���� ����
    int discard = 0;     // scanf �Լ����� ��ȯ�� ���� �������� ���� ����

    // ����� �Է� ó��
    printf("�غ� �Է�: ");
    discard = scanf("%lf", &width);
    printf("���� �Է�: ");
    discard = scanf("%lf", &height);

    // �簢�� ���� ���
    area = width * height;

    // ��� ���
    printf("�簢���� ����: %.2lf ��� ����\n", area);

    return 0;
}
