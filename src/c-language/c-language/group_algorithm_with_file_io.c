// Visual Studio에서 보안 경고를 무시하도록 설정 (fopen 등에서 경고 방지)
#define _CRT_SECURE_NO_WARNINGS

// C 표준 라이브러리 헤더 포함
#include <stdio.h>      // 파일 입출력 관련 함수: fopen, fclose, printf, fprintf 등
#include <stdlib.h>     // 표준 유틸리티 함수: atoi, exit 등
#include <string.h>     // 문자열 처리 함수: strlen, strncpy, strcmp, strcpy
#include <stdbool.h>    // bool, true, false 사용을 위한 헤더

#include <sys/stat.h>   // 파일 상태 확인용: stat() 함수 사용

// 상수 정의: 최대 레코드 수, 한 줄당 최대 문자열 길이, 파일 경로
#define MAX_RECORDS 100
#define LINE_LENGTH 16
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"    // 입력 파일 경로
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"   // 출력 파일 경로

// 구조체 정의: 상품명 + 판매량으로 구성된 레코드
typedef struct
{
    char product_name[6];  // 상품명 (5자 + 문자열 종료 NULL 포함)
    int quantity;          // 판매량
} record_t;

// 문자열 끝의 개행 문자 '\n'을 제거하는 보조 함수
// fgets()로 읽은 문자열 뒤에 붙는 줄바꿈 문자를 제거해야 정확한 문자열 비교가 가능
void trim_newline(char* str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';  // 줄바꿈 문자를 NULL 문자로 대체
    }
}

// 파일 존재 여부를 확인하는 함수
// stat() 함수가 0을 반환하면 해당 경로에 파일이 존재한다는 의미
bool file_exists(const char* path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

// 입력 파일이 존재하지 않을 경우 샘플 데이터를 자동으로 생성하는 함수
// 기본 입력 데이터를 txt 파일에 기록함
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");  // 쓰기 모드로 파일 열기
    if (file == NULL)
    {
        perror("입력 파일 생성 실패");
        exit(EXIT_FAILURE);  // 에러 발생 시 프로그램 종료
    }

    // 샘플 데이터 (상품명 + 판매량)
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

    // 배열 크기만큼 루프 돌며 파일에 한 줄씩 기록
    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);  // 파일 닫기
    printf("샘플 입력 파일이 생성되었습니다: %s\n", INPUT_FILE_PATH);
}

// 입력 파일을 읽어 records 배열에 저장하고, 읽은 레코드 수를 반환하는 함수
int read_records(FILE* input_file, record_t* records)
{
    int count = 0;
    char input_line[LINE_LENGTH];  // 한 줄씩 읽을 임시 버퍼

    // 파일 끝까지 또는 최대 레코드 수만큼 반복
    while (fgets(input_line, LINE_LENGTH, input_file) != NULL && count < MAX_RECORDS)
    {
        trim_newline(input_line);  // 줄바꿈 제거

        // 최소 길이(8자) 이상인 경우만 유효한 데이터로 처리
        if (strlen(input_line) >= 8)
        {
            // 앞 5글자는 상품명
            strncpy(records[count].product_name, input_line, 5);
            records[count].product_name[5] = '\0';  // 문자열 종료 처리

            // 6번째 문자부터 판매량 (공백 포함 가능)
            records[count].quantity = atoi(input_line + 5);
            count++;
        }
    }

    return count;  // 실제 읽은 레코드 수 반환
}

// 상품명을 기준으로 오름차순 정렬하는 함수 (선택 정렬)
void sort_records(record_t* records, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            // [!] 사전 순으로 더 앞선 상품명이 있으면 교환 (선택 정렬 방식)
            if (strcmp(records[i].product_name, records[j].product_name) > 0)
            {
                record_t temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
}

// 동일한 상품명을 가진 항목들을 묶고, 판매량을 합산하여 grouped 배열에 저장하는 함수
// 그룹 수를 반환
int group_records(const record_t* records, int count, record_t* grouped)
{
    int group_count = 0;
    int group_total = 0;

    for (int i = 0; i < count; i++)
    {
        group_total += records[i].quantity;

        bool is_last = (i == count - 1);
        // 다음 상품명과 다르거나 마지막 항목이면 그룹 경계
        bool group_boundary_detected = is_last || strcmp(records[i].product_name, records[i + 1].product_name) != 0;

        if (group_boundary_detected)
        {
            // 그룹화된 상품명 및 총 판매량 저장
            strcpy(grouped[group_count].product_name, records[i].product_name);
            grouped[group_count].quantity = group_total;
            group_count++;
            group_total = 0;  // 다음 그룹을 위해 초기화
        }
    }

    return group_count;
}

// 레코드 배열을 콘솔에 출력하는 함수
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s %d\n", records[i].product_name, records[i].quantity);
    }
}

// 레코드 배열을 파일에 출력하는 함수
void write_records(FILE* file, const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s %d\n", records[i].product_name, records[i].quantity);
    }
}

// 프로그램 진입점
int main(void)
{
    // 입력 데이터를 저장할 배열
    record_t records[MAX_RECORDS];
    // 그룹화된 결과를 저장할 배열
    record_t grouped[MAX_RECORDS];

    // [0] 입력 파일이 없으면 샘플 데이터를 자동으로 생성
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    // 파일 열기: 입력 파일은 읽기 모드, 출력 파일은 쓰기 모드
    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");

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
