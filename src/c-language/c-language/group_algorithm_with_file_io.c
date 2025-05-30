// Visual Studio에서 보안 경고를 무시하도록 설정 (fopen 등에서 경고 방지)
#define _CRT_SECURE_NO_WARNINGS

// C 표준 라이브러리 헤더 포함
#include <stdio.h>      // 파일 입출력 관련 함수: fopen, fclose, printf, fprintf 등
#include <stdlib.h>     // 표준 유틸리티 함수: atoi, exit 등
#include <string.h>     // 문자열 처리 함수: strcmp, strcpy
#include <stdbool.h>    // bool, true, false 사용을 위한 헤더

// 상수 정의
#define MAX_RECORDS 100
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"    // 입력 파일 경로
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"   // 출력 파일 경로

// 구조체 정의: 상품명 + 판매량으로 구성된 레코드
typedef struct
{
    char product_name[6];  // 상품명 (5자 + NULL 종료 문자)
    int quantity;          // 판매량
} record_t;

// 파일 존재 여부 확인 함수
bool file_exists(const char* path) {
    FILE* file = fopen(path, "r");  // 읽기 모드로 열기 시도
    if (file != NULL) {
        fclose(file);  // 열렸으면 닫고
        return true;   // 존재함
    }
    return false;      // 열리지 않으면 존재하지 않음
}

// 입력 파일이 존재하지 않을 경우 샘플 데이터를 자동 생성
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");  // 텍스트 쓰기 모드로 파일 열기
    if (file == NULL)
    {
        perror("입력 파일 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 샘플 데이터
    const char* lines[] = {
        "RADIO  5",
        "TV     6",
        "PHONE  3",
        "RADIO  2",
        "PHONE  2",
        "TV    10",
        "PHONE 11",
        "TV     7",
        "PHONE  4"
    };

    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++)
    {
        fprintf(file, "%s\n", lines[i]);  // 각 줄을 파일에 저장
    }

    fclose(file);
    printf("샘플 입력 파일이 생성되었습니다: %s\n", INPUT_FILE_PATH);
}

// fscanf를 이용해 파일에서 레코드 읽기
int read_records(FILE* input_file, record_t* records)
{
    int count = 0;

    while (count < MAX_RECORDS)
    {
        // 파일에서 상품명(최대 5자)과 판매량(정수)을 읽음
        int result = fscanf(input_file, "%5s%3d", records[count].product_name, &records[count].quantity);

        if (result != 2)
        {
            // 두 항목을 모두 읽지 못했으면 반복 중단
            break;
        }

        count++;  // 유효한 레코드 수 증가
    }

    return count;  // 실제 읽은 레코드 수 반환
}

// 선택 정렬로 상품명을 기준으로 오름차순 정렬
void sort_records(record_t* records, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(records[i].product_name, records[j].product_name) > 0)
            {
                record_t temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
}

// 동일한 상품명을 가진 항목을 묶어 판매량 합산
int group_records(const record_t* records, int count, record_t* grouped)
{
    int group_count = 0;
    int group_total = 0;

    for (int i = 0; i < count; i++)
    {
        group_total += records[i].quantity;  // 누적 합산

        bool is_last = (i == count - 1);  // 마지막 항목 여부
        bool boundary = is_last || strcmp(records[i].product_name, records[i + 1].product_name) != 0;  // 그룹 경계 조건

        if (boundary)
        {
            strcpy(grouped[group_count].product_name, records[i].product_name);
            grouped[group_count].quantity = group_total;  // 그룹 판매량 저장
            group_count++;
            group_total = 0;  // 초기화
        }
    }

    return group_count;
}

// 콘솔 출력 함수 (정렬된 출력)
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%-5s%3d\n", records[i].product_name, records[i].quantity);  // 이름 왼쪽 정렬, 수량 오른쪽 정렬
    }
}

// 파일 출력 함수 (정렬된 출력)
void write_records(FILE* file, const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%-5s%3d\n", records[i].product_name, records[i].quantity);  // 이름 왼쪽 정렬, 수량 오른쪽 정렬
    }
}

// main 함수: 프로그램 시작점
int main(void)
{
    record_t records[MAX_RECORDS];    // 입력 데이터 저장용
    record_t grouped[MAX_RECORDS];    // 그룹화 결과 저장용

    // [0] 입력 파일이 없으면 샘플 파일 생성
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    // 파일 열기
    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");    // 읽기 모드
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");  // 쓰기 모드

    if (input_file == NULL || output_file == NULL)
    {
        perror("파일 열기 실패");
        return EXIT_FAILURE;
    }

    // [1] 파일에서 데이터 읽기
    int record_count = read_records(input_file, records);
    printf("입력된 상품 데이터 (%d개):\n", record_count);
    print_records(records, record_count);

    // [2] 정렬
    sort_records(records, record_count);
    printf("\n정렬된 데이터:\n");
    print_records(records, record_count);

    // [3] 그룹화
    int group_count = group_records(records, record_count, grouped);
    printf("\n상품별 판매량 집계 결과:\n");
    print_records(grouped, group_count);

    // [4] 결과를 파일로 저장
    write_records(output_file, grouped, group_count);

    // 파일 닫기
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
