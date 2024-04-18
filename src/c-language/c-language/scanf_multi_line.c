// scanf_multi_line.c
// 다중 행 입력 처리 예제
#define _CRT_SECURE_NO_WARNINGS // scanf 보안 경고 방지
#include <stdio.h>

int main(void)
{
    char name[20];
    int age;
    char nick[20];
    int discard; // 반환된 값을 저장하지 않는 변수

    printf("입력\n----\n");
    printf("이름: "); discard = scanf(" %s", name); // 공백을 서식 지정자 앞에 추가
    printf("나이: "); discard = scanf(" %d", &age);
    printf("별명: "); discard = scanf(" %s", nick);

    printf("\n출력\n----\n");
    printf("이름: %s\n", name);
    printf("나이: %d\n", age);
    printf("별명: %s\n", nick);

    return 0;
}
