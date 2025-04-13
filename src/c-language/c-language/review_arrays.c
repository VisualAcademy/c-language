#include <stdio.h>

int main(void)
{
    int numbers[] = { 10, 20, 30, 40, 50 };  // 정수형 배열 선언 및 초기화

    // 배열 요소를 하나씩 출력
    for (int i = 0; i < 5; i++)
    {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    return 0;
}