#include <stdio.h>

// �Լ� ����: ��ȯ�� void, �Ű����� ����
void sayHello(void);

int main(void)
{
    sayHello();  // �Լ� ȣ��
    return 0;
}

// �Լ� ����: "Hello, World!" ���
void sayHello(void)
{
    printf("Hello, World!\n");
}