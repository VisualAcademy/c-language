#include <stdio.h>

// 함수 선언: 정수를 매개변수로 받음
void printNumber(int num);

// 함수 선언: 두 개의 정수를 매개변수로 받아 합을 출력
void printSum(int a, int b);

int main(void)
{
    printNumber(5);  // 숫자 5를 전달하여 함수 호출
    printNumber(10);  // 숫자 10을 전달하여 함수 호출

    printSum(3, 7);  // 숫자 3과 7을 전달하여 합을 출력
    printSum(10, 20);  // 숫자 10과 20을 전달하여 합을 출력

    return 0;
}

// 함수 정의: 전달받은 정수를 출력
void printNumber(int num)
{
    printf("전달받은 숫자: %d\n", num);
}

// 함수 정의: 전달받은 두 정수의 합을 출력
void printSum(int a, int b)
{
    int sum = a + b;
    printf("두 수의 합: %d\n", sum);
}