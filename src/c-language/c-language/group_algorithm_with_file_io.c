// Visual Studio���� ���� ��� �����ϵ��� ���� (fopen ��� ��� ����)
#define _CRT_SECURE_NO_WARNINGS

// C ǥ�� ���̺귯�� ��� ����
#include <stdio.h>      // ���� ����� ���� �Լ�: fopen, fclose, printf, fprintf ��
#include <stdlib.h>     // ǥ�� ��ƿ��Ƽ �Լ�: atoi, exit ��
#include <string.h>     // ���ڿ� ó�� �Լ�: strlen, strncpy, strcmp, strcpy
#include <stdbool.h>    // bool, true, false ����� ���� ���

#include <sys/stat.h>   // ���� ���� Ȯ�ο�: stat() �Լ� ���

// ��� ����: �ִ� ���ڵ� ��, �� �ٴ� �ִ� ���ڿ� ����, ���� ���
#define MAX_RECORDS 100
#define LINE_LENGTH 16
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"    // �Է� ���� ���
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"   // ��� ���� ���

// ����ü ����: ��ǰ�� + �Ǹŷ����� ������ ���ڵ�
typedef struct
{
    char product_name[6];  // ��ǰ�� (5�� + ���ڿ� ���� NULL ����)
    int quantity;          // �Ǹŷ�
} record_t;

// ���ڿ� ���� ���� ���� '\n'�� �����ϴ� ���� �Լ�
// fgets()�� ���� ���ڿ� �ڿ� �ٴ� �ٹٲ� ���ڸ� �����ؾ� ��Ȯ�� ���ڿ� �񱳰� ����
void trim_newline(char* str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';  // �ٹٲ� ���ڸ� NULL ���ڷ� ��ü
    }
}

// ���� ���� ���θ� Ȯ���ϴ� �Լ�
// stat() �Լ��� 0�� ��ȯ�ϸ� �ش� ��ο� ������ �����Ѵٴ� �ǹ�
bool file_exists(const char* path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

// �Է� ������ �������� ���� ��� ���� �����͸� �ڵ����� �����ϴ� �Լ�
// �⺻ �Է� �����͸� txt ���Ͽ� �����
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");  // ���� ���� ���� ����
    if (file == NULL)
    {
        perror("�Է� ���� ���� ����");
        exit(EXIT_FAILURE);  // ���� �߻� �� ���α׷� ����
    }

    // ���� ������ (��ǰ�� + �Ǹŷ�)
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

    // �迭 ũ�⸸ŭ ���� ���� ���Ͽ� �� �پ� ���
    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);  // ���� �ݱ�
    printf("���� �Է� ������ �����Ǿ����ϴ�: %s\n", INPUT_FILE_PATH);
}

// �Է� ������ �о� records �迭�� �����ϰ�, ���� ���ڵ� ���� ��ȯ�ϴ� �Լ�
int read_records(FILE* input_file, record_t* records)
{
    int count = 0;
    char input_line[LINE_LENGTH];  // �� �پ� ���� �ӽ� ����

    // ���� ������ �Ǵ� �ִ� ���ڵ� ����ŭ �ݺ�
    while (fgets(input_line, LINE_LENGTH, input_file) != NULL && count < MAX_RECORDS)
    {
        trim_newline(input_line);  // �ٹٲ� ����

        // �ּ� ����(8��) �̻��� ��츸 ��ȿ�� �����ͷ� ó��
        if (strlen(input_line) >= 8)
        {
            // �� 5���ڴ� ��ǰ��
            strncpy(records[count].product_name, input_line, 5);
            records[count].product_name[5] = '\0';  // ���ڿ� ���� ó��

            // 6��° ���ں��� �Ǹŷ� (���� ���� ����)
            records[count].quantity = atoi(input_line + 5);
            count++;
        }
    }

    return count;  // ���� ���� ���ڵ� �� ��ȯ
}

// ��ǰ���� �������� �������� �����ϴ� �Լ� (���� ����)
void sort_records(record_t* records, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            // [!] ���� ������ �� �ռ� ��ǰ���� ������ ��ȯ (���� ���� ���)
            if (strcmp(records[i].product_name, records[j].product_name) > 0)
            {
                record_t temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
}

// ������ ��ǰ���� ���� �׸���� ����, �Ǹŷ��� �ջ��Ͽ� grouped �迭�� �����ϴ� �Լ�
// �׷� ���� ��ȯ
int group_records(const record_t* records, int count, record_t* grouped)
{
    int group_count = 0;
    int group_total = 0;

    for (int i = 0; i < count; i++)
    {
        group_total += records[i].quantity;

        bool is_last = (i == count - 1);
        // ���� ��ǰ��� �ٸ��ų� ������ �׸��̸� �׷� ���
        bool group_boundary_detected = is_last || strcmp(records[i].product_name, records[i + 1].product_name) != 0;

        if (group_boundary_detected)
        {
            // �׷�ȭ�� ��ǰ�� �� �� �Ǹŷ� ����
            strcpy(grouped[group_count].product_name, records[i].product_name);
            grouped[group_count].quantity = group_total;
            group_count++;
            group_total = 0;  // ���� �׷��� ���� �ʱ�ȭ
        }
    }

    return group_count;
}

// ���ڵ� �迭�� �ֿܼ� ����ϴ� �Լ�
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s %d\n", records[i].product_name, records[i].quantity);
    }
}

// ���ڵ� �迭�� ���Ͽ� ����ϴ� �Լ�
void write_records(FILE* file, const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s %d\n", records[i].product_name, records[i].quantity);
    }
}

// ���α׷� ������
int main(void)
{
    // �Է� �����͸� ������ �迭
    record_t records[MAX_RECORDS];
    // �׷�ȭ�� ����� ������ �迭
    record_t grouped[MAX_RECORDS];

    // [0] �Է� ������ ������ ���� �����͸� �ڵ����� ����
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    // ���� ����: �Է� ������ �б� ���, ��� ������ ���� ���
    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");

    if (input_file == NULL || output_file == NULL)
    {
        perror("���� ���� ����");
        return EXIT_FAILURE;
    }

    // [1] ���Ͽ��� ������ �б�
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

    // [4] ����� ���Ϸ� ����
    write_records(output_file, grouped, group_count);

    // ���� �ݱ�
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
