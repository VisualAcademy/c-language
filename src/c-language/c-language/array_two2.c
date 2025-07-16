//[?] 이차원 배열 선언과 동시에 초기화
#include <stdio.h>

int main(void)
{
    // 2차원 배열 선언과 동시에 초기화 
    int intArray[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };

    // 2중 for 문으로 2차원 배열 출력
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d\t", intArray[i][j]);
        }
        printf("\n"); // 행 출력 후 줄바꿈
    }

    return 0;
}
