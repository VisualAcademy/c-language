#include <stdio.h>

int main(void)
{
    int number = 123;  // 정수형 변수 선언 및 초기화
    float pi = 3.14;  // 실수형 변수 선언 및 초기화
    char letter = 'A';  // 문자형 변수 선언 및 초기화
    char string[] = "Hello";  // 문자열 변수 선언 및 초기화

    printf("정수: %d\n", number);
    printf("실수: %.2f\n", pi);
    printf("문자: %c\n", letter);
    printf("문자열: %s\n", string);

    return 0;
}