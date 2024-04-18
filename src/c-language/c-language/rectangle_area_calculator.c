// C 언어를 이용한 사각형의 넓이 계산 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    // 변수 선언
    double width = 0.0;  // 밑변
    double height = 0.0; // 높이
    double area = 0.0;   // 계산된 넓이
    int discard = 0;     // scanf 함수에서 반환된 값을 저장하지 않을 변수

    // 사용자 입력 처리
    printf("밑변 입력: ");
    discard = scanf("%lf", &width);
    printf("높이 입력: ");
    discard = scanf("%lf", &height);

    // 사각형 넓이 계산
    area = width * height;

    // 결과 출력
    printf("사각형의 넓이: %.2lf 평방 단위\n", area);

    return 0;
}
