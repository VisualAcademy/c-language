#include <stdio.h>

int main(void)
{
    int num = 10;  // 검사할 숫자 변수

    if (num > 0)  // 양수인지 검사
    {
        printf("양수입니다.\n");
    }
    else if (num < 0)  // 음수인지 검사
    {
        printf("음수입니다.\n");
    }
    else  // 0인 경우
    {
        printf("0입니다.\n");
    }

    return 0;
}