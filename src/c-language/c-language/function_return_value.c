// 반환값이 있는 함수
#include <stdio.h>

int SquareFunction(int x)   // 입력: 매개 변수가 있음
{
    int r = x * x;          // 처리: 함수의 본문
    return r;               // 출력: 반환값이 있음
}

int main(void)
{
    int r = SquareFunction(2); // 함수를 호출하고 반환값을 받음
    printf("%d\n", r); // 출력: 4

    return 0;
}