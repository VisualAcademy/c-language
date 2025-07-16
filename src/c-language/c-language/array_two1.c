//[?] 이차원 배열 생성 및 반복문으로 출력하기
#include <stdio.h>

int main(void)
{
    // 2차원 배열 선언
    int intArray[2][3];

    // 2차원 배열 초기화 
    intArray[0][0] = 1;
    intArray[0][1] = 2;
    intArray[0][2] = 3;

    intArray[1][0] = 4;
    intArray[1][1] = 5;
    intArray[1][2] = 6;

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
