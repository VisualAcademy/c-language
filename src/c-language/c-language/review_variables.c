#include <stdio.h>

int main(void)
{
    int number = 123;  // ������ ���� ���� �� �ʱ�ȭ
    float pi = 3.14;  // �Ǽ��� ���� ���� �� �ʱ�ȭ
    char letter = 'A';  // ������ ���� ���� �� �ʱ�ȭ
    char string[] = "Hello";  // ���ڿ� ���� ���� �� �ʱ�ȭ

    printf("����: %d\n", number);
    printf("�Ǽ�: %.2f\n", pi);
    printf("����: %c\n", letter);
    printf("���ڿ�: %s\n", string);

    return 0;
}