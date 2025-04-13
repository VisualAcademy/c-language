#include <stdio.h>

// 함수 선언: 반환형 void, 매개변수 없음
void sayHello(void);

int main(void)
{
    sayHello();  // 함수 호출
    return 0;
}

// 함수 정의: "Hello, World!" 출력
void sayHello(void)
{
    printf("Hello, World!\n");
}