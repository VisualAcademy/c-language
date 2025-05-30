// Visual Studio에서 보안 경고를 무시하도록 설정 (fopen 등에서 경고 방지)
#define _CRT_SECURE_NO_WARNINGS

// C 표준 라이브러리 헤더 포함
#include <stdio.h>      // 파일 입출력 관련 함수: fopen, fclose, printf, fprintf 등
#include <stdlib.h>     // 표준 유틸리티 함수: atoi, exit 등
#include <string.h>     // 문자열 처리 함수: strcmp, strcpy
#include <stdbool.h>    // bool, true, false 사용을 위한 헤더

// 상수 정의
#define MAX_RECORDS 100                                 // 최대 레코드 수
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"        // 입력 파일 경로
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"       // 출력 파일 경로

// 구조체 정의: 상품명 + 판매량으로 구성된 레코드
typedef struct
{
    char product_name[6];  // 상품명 (최대 5자 + 종료 문자 '\0')
    int quantity;          // 판매량 (정수)
} record_t;

// 파일 존재 여부 확인 함수
// fopen으로 파일을 열어보고 성공하면 true, 실패하면 false 반환
bool file_exists(const char* path) 
{
    FILE* file = fopen(path, "r");  // 읽기 모드로 열기 시도
    if (file != NULL) 
    {
        fclose(file);  // 파일이 존재하므로 닫고 true 반환
        return true;
    }
    return false;      // 파일 열기 실패 → 존재하지 않음
}

// 입력 파일이 없을 경우 샘플 데이터를 자동으로 생성
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");  // 텍스트 쓰기 모드로 파일 열기
    if (file == NULL)
    {
        perror("입력 파일 생성 실패");  // 파일 생성 오류 출력
        exit(EXIT_FAILURE);            // 프로그램 강제 종료
    }

    // 샘플 데이터 (상품명은 5자리, 숫자는 최대 3자리로 자릿수 고정)
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

    // 배열에 있는 샘플 데이터를 한 줄씩 파일에 저장
    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);  // 파일 닫기
    printf("샘플 입력 파일이 생성되었습니다: %s\n", INPUT_FILE_PATH);
}

// fscanf를 이용해 파일에서 레코드 읽기
int read_records(FILE* input_file, record_t* records)
{
    int count = 0;

    while (count < MAX_RECORDS)
    {
        // 서식 설명:
        // "%5s"  : 최대 5글자까지 문자열 읽기 (공백 없이)
        // "%3d"  : 최대 3자리 정수 읽기 (숫자 앞에 공백 있어도 허용)
        int result = fscanf(input_file, "%5s%3d", records[count].product_name, &records[count].quantity);

        if (result != 2)  // 두 개 모두 못 읽으면 반복 중지
            break;

        count++;  // 유효한 레코드 수 증가
    }

    return count;  // 실제 읽은 레코드 수 반환
}

// 상품명을 기준으로 오름차순 정렬 (선택 정렬 방식)
void sort_records(record_t* records, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            // 문자열 비교: i번째보다 j번째가 사전순으로 앞서면 교환
            if (strcmp(records[i].product_name, records[j].product_name) > 0)
            {
                // 값 교환
                record_t temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
}

// 동일한 상품명을 가진 항목을 묶어 판매량을 합산
int group_records(const record_t* records, int count, record_t* grouped)
{
    int group_count = 0;
    int group_total = 0;

    for (int i = 0; i < count; i++)
    {
        group_total += records[i].quantity;  // 현재 항목의 판매량을 누적

        // 그룹의 마지막 항목인지 확인
        bool is_last = (i == count - 1);
        bool boundary = is_last || strcmp(records[i].product_name, records[i + 1].product_name) != 0;

        if (boundary)
        {
            // 그룹 정보를 grouped 배열에 저장
            strcpy(grouped[group_count].product_name, records[i].product_name);
            grouped[group_count].quantity = group_total;
            group_count++;
            group_total = 0;  // 다음 그룹을 위해 초기화
        }
    }

    return group_count;  // 그룹 개수 반환
}

// 콘솔에 레코드 배열을 출력
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        // 상품명은 왼쪽 정렬, 수량은 오른쪽 정렬
        printf("%-5s%3d\n", records[i].product_name, records[i].quantity);
    }
}

// 파일에 레코드 배열을 출력
void write_records(FILE* file, const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%-5s%3d\n", records[i].product_name, records[i].quantity);
    }
}

// main 함수: 프로그램 시작점
int main(void)
{
    record_t records[MAX_RECORDS];    // 원본 데이터 저장용 배열
    record_t grouped[MAX_RECORDS];    // 그룹화된 결과 저장용 배열

    // [0] 파일이 없으면 샘플 데이터 자동 생성
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    // 파일 열기
    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");    // 텍스트 읽기 모드
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");  // 텍스트 쓰기 모드

    if (input_file == NULL || output_file == NULL)
    {
        perror("파일 열기 실패");  // 파일 열기 실패 메시지 출력
        return EXIT_FAILURE;       // 프로그램 비정상 종료
    }

    // [1] 파일에서 데이터 읽기
    int record_count = read_records(input_file, records);
    printf("입력된 상품 데이터 (%d개):\n", record_count);
    print_records(records, record_count);

    // [2] 상품명 기준 정렬
    sort_records(records, record_count);
    printf("\n정렬된 데이터:\n");
    print_records(records, record_count);

    // [3] 동일 상품명끼리 판매량 합산 (그룹화)
    int group_count = group_records(records, record_count, grouped);
    printf("\n상품별 판매량 집계 결과:\n");
    print_records(grouped, group_count);

    // [4] 결과를 출력 파일로 저장
    write_records(output_file, grouped, group_count);

    // [5] 파일 닫기
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;  // 프로그램 정상 종료
}
