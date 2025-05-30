#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      // FILE, fopen, fclose, printf, fprintf, perror
#include <stdlib.h>     // atoi, EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>     // strncpy, strcmp, strlen, strcpy
#include <stdbool.h>    // bool, true, false

#include <sys/stat.h>   // stat (���� ���� ���� Ȯ�ο�)
#define MAX_RECORDS 100
#define LINE_LENGTH 16
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"

typedef struct
{
    char product_name[6];  // ��ǰ�� (5���� + '\0')
    int quantity;
} record_t;

// (Optional) �� ���� �ٴ� ���� ���ڸ� �����ϴ� ���� �Լ��Դϴ�.
// fgets()�� ���� ���ڿ��� ���ϰų� ������ �� ����������,
// ���� �ڵ忡���� ��� ū ���� ���� ������ �� �ֽ��ϴ�.
void trim_newline(char* str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

// (Reference only) ������ �����ϴ����� Ȯ���ϴ� ������ ��ƿ��Ƽ �Լ��Դϴ�.
// ������ ���� ��� �Է� ������ ���� ����� �������� ���Ǹ�,
// ���� �ý����� �ٷ� �� ���� �������� C ��� �Թ��ڿ��� ������ �� �ֽ��ϴ�.
bool file_exists(const char* path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

// �Է� ������ ���� ��� �ڵ����� ����
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");
    if (file == NULL)
    {
        perror("�Է� ���� ���� ����");
        exit(EXIT_FAILURE);
    }

    // ���� ������ �ۼ�
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
    printf("���� �Է� ������ �����Ǿ����ϴ�: %s\n", INPUT_FILE_PATH);
}

// ���Ͽ��� ���ڵ� �б�
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

// ����
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

// �׷�ȭ
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

// ���
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s %d\n", records[i].product_name, records[i].quantity);
    }
}

// ���Ϸ� ���
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

    // [0] �Է� ������ ������ �ڵ� ����
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");

    if (input_file == NULL || output_file == NULL)
    {
        perror("���� ���� ����");
        return EXIT_FAILURE;
    }

    // [1] �Է�
    int record_count = read_records(input_file, records);
    printf("�Էµ� ��ǰ ������ (%d��):\n", record_count);
    print_records(records, record_count);

    // [2] ����
    sort_records(records, record_count);
    printf("\n���ĵ� ������:\n");
    print_records(records, record_count);

    // [3] �׷�ȭ
    int group_count = group_records(records, record_count, grouped);
    printf("\n��ǰ�� �Ǹŷ� ���� ���:\n");
    print_records(grouped, group_count);

    // [4] ���� ����
    write_records(output_file, grouped, group_count);

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
