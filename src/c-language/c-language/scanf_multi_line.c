// scanf_multi_line.c
// ���� �� �Է� ó�� ����
#define _CRT_SECURE_NO_WARNINGS // scanf ���� ��� ����
#include <stdio.h>

int main(void)
{
    char name[20];
    int age;
    char nick[20];
    int discard; // ��ȯ�� ���� �������� �ʴ� ����

    printf("�Է�\n----\n");
    printf("�̸�: "); discard = scanf(" %s", name); // ������ ���� ������ �տ� �߰�
    printf("����: "); discard = scanf(" %d", &age);
    printf("����: "); discard = scanf(" %s", nick);

    printf("\n���\n----\n");
    printf("�̸�: %s\n", name);
    printf("����: %d\n", age);
    printf("����: %s\n", nick);

    return 0;
}
