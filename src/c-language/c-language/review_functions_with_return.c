#include <stdio.h>

// 함수 선언: 정수를 매개변수로 받아 제곱값을 반환
int square(int num);

int main(void)
{
    int result = square(4);  // 숫자 4의 제곱값을 함수로부터 반환받음
    printf("4의 제곱: %d\n", result);

    printf("7의 제곱: %d\n", square(7));  // 반환값을 바로 출력
    return 0;
}

// 함수 정의: 전달받은 정수의 제곱값 반환
int square(int num)
{
    return num * num;
}