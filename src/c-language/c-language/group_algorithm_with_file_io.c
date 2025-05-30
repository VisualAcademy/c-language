#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      // FILE, fopen, fclose, printf, fprintf, perror
#include <stdlib.h>     // atoi, EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>     // strncpy, strcmp, strlen, strcpy
#include <stdbool.h>    // bool, true, false

#include <sys/stat.h>   // stat (파일 존재 여부 확인용)
#define MAX_RECORDS 100
#define LINE_LENGTH 16
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"

typedef struct
{
    char product_name[6];  // 상품명 (5글자 + '\0')
    int quantity;
} record_t;

// (Optional) 줄 끝에 붙는 개행 문자를 제거하는 보조 함수입니다.
// fgets()로 읽은 문자열을 비교하거나 가공할 때 유용하지만,
// 현재 코드에서는 없어도 큰 문제 없이 동작할 수 있습니다.
void trim_newline(char* str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

// (Reference only) 파일이 존재하는지를 확인하는 간단한 유틸리티 함수입니다.
// 파일이 없을 경우 입력 파일을 새로 만드는 로직에서 사용되며,
// 파일 시스템을 다룰 때 자주 쓰이지만 C 언어 입문자에겐 생소할 수 있습니다.
bool file_exists(const char* path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

// 입력 파일이 없을 경우 자동으로 생성
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");
    if (file == NULL)
    {
        perror("입력 파일 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 샘플 데이터 작성
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
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
    printf("샘플 입력 파일이 생성되었습니다: %s\n", INPUT_FILE_PATH);
}

// 파일에서 레코드 읽기
int read_records(FILE* input_file, record_t* records)
{
    int count = 0;
    char input_line[LINE_LENGTH];

    while (fgets(input_line, LINE_LENGTH, input_file) != NULL && count < MAX_RECORDS)
    {
        trim_newline(input_line);
        if (strlen(input_line) >= 8)
        {
            strncpy(records[count].product_name, input_line, 5);
            records[count].product_name[5] = '\0';
            records[count].quantity = atoi(input_line + 5);
            count++;
        }
    }

    return count;
}

// 정렬
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

// 그룹화
int group_records(const record_t* records, int count, record_t* grouped)
{
    int group_count = 0;
    int group_total = 0;

    for (int i = 0; i < count; i++)
    {
        group_total += records[i].quantity;

        bool is_last = (i == count - 1);
        bool group_boundary_detected = is_last || strcmp(records[i].product_name, records[i + 1].product_name) != 0;

        if (group_boundary_detected)
        {
            strcpy(grouped[group_count].product_name, records[i].product_name);
            grouped[group_count].quantity = group_total;
            group_count++;
            group_total = 0;
        }
    }

    return group_count;
}

// 출력
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s %d\n", records[i].product_name, records[i].quantity);
    }
}

// 파일로 출력
void write_records(FILE* file, const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s %d\n", records[i].product_name, records[i].quantity);
    }
}

int main(void)
{
    record_t records[MAX_RECORDS];
    record_t grouped[MAX_RECORDS];

    // [0] 입력 파일이 없으면 자동 생성
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");

    if (input_file == NULL || output_file == NULL)
    {
        perror("파일 열기 실패");
        return EXIT_FAILURE;
    }

    // [1] 입력
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

    // [4] 파일 저장
    write_records(output_file, grouped, group_count);

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
