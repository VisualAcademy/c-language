#include <stdio.h>

int main(void)
{
    // 집합 A와 B 정의
    int A[5] = { 0, 1, 8, 9, 6 };
    int B[3] = { 1, 6, 7 };

    int first = 1; // 교집합의 첫 번째 원소인지 여부 체크용 변수

    // 교집합 출력 시작
    printf("A INTERSECTION B = {");
    for (int i = 0; i < 5; i++)            // 집합 A의 모든 원소 반복
    {
        for (int j = 0; j < 3; j++)        // 집합 B의 모든 원소 반복
        {
            if (A[i] == B[j])              // 두 원소가 같으면 교집합 원소
            {
                if (first)                 // 첫 번째 원소일 경우
                {
                    printf("%d", A[i]);    // 그냥 출력
                    first = 0;             // 첫 번째 출력 끝났음을 표시
                }
                else
                {
                    printf(", %d", A[i]);  // 그 이후 원소는 ", " 붙여서 출력
                }
            }
        }
    }
    printf("}\n"); // 교집합 출력 마무리

    return 0;
}
