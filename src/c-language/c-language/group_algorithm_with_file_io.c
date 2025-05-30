// Visual Studio���� ���� ��� �����ϵ��� ���� (fopen ��� ��� ����)
#define _CRT_SECURE_NO_WARNINGS

// C ǥ�� ���̺귯�� ��� ����
#include <stdio.h>      // ���� ����� ���� �Լ�: fopen, fclose, printf, fprintf ��
#include <stdlib.h>     // ǥ�� ��ƿ��Ƽ �Լ�: atoi, exit ��
#include <string.h>     // ���ڿ� ó�� �Լ�: strcmp, strcpy
#include <stdbool.h>    // bool, true, false ����� ���� ���

// ��� ����
#define MAX_RECORDS 100
#define INPUT_FILE_PATH  "C:\\Temp\\abc1229.txt"    // �Է� ���� ���
#define OUTPUT_FILE_PATH "C:\\Temp\\abc1229_.txt"   // ��� ���� ���

// ����ü ����: ��ǰ�� + �Ǹŷ����� ������ ���ڵ�
typedef struct
{
    char product_name[6];  // ��ǰ�� (5�� + NULL ���� ����)
    int quantity;          // �Ǹŷ�
} record_t;

// ���� ���� ���� Ȯ�� �Լ�
bool file_exists(const char* path) {
    FILE* file = fopen(path, "r");  // �б� ���� ���� �õ�
    if (file != NULL) {
        fclose(file);  // �������� �ݰ�
        return true;   // ������
    }
    return false;      // ������ ������ �������� ����
}

// �Է� ������ �������� ���� ��� ���� �����͸� �ڵ� ����
void create_sample_input_file()
{
    FILE* file = fopen(INPUT_FILE_PATH, "wt");  // �ؽ�Ʈ ���� ���� ���� ����
    if (file == NULL)
    {
        perror("�Է� ���� ���� ����");
        exit(EXIT_FAILURE);
    }

    // ���� ������
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
        fprintf(file, "%s\n", lines[i]);  // �� ���� ���Ͽ� ����
    }

    fclose(file);
    printf("���� �Է� ������ �����Ǿ����ϴ�: %s\n", INPUT_FILE_PATH);
}

// fscanf�� �̿��� ���Ͽ��� ���ڵ� �б�
int read_records(FILE* input_file, record_t* records)
{
    int count = 0;

    while (count < MAX_RECORDS)
    {
        // ���Ͽ��� ��ǰ��(�ִ� 5��)�� �Ǹŷ�(����)�� ����
        int result = fscanf(input_file, "%5s%3d", records[count].product_name, &records[count].quantity);

        if (result != 2)
        {
            // �� �׸��� ��� ���� �������� �ݺ� �ߴ�
            break;
        }

        count++;  // ��ȿ�� ���ڵ� �� ����
    }

    return count;  // ���� ���� ���ڵ� �� ��ȯ
}

// ���� ���ķ� ��ǰ���� �������� �������� ����
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

// ������ ��ǰ���� ���� �׸��� ���� �Ǹŷ� �ջ�
int group_records(const record_t* records, int count, record_t* grouped)
{
    int group_count = 0;
    int group_total = 0;

    for (int i = 0; i < count; i++)
    {
        group_total += records[i].quantity;  // ���� �ջ�

        bool is_last = (i == count - 1);  // ������ �׸� ����
        bool boundary = is_last || strcmp(records[i].product_name, records[i + 1].product_name) != 0;  // �׷� ��� ����

        if (boundary)
        {
            strcpy(grouped[group_count].product_name, records[i].product_name);
            grouped[group_count].quantity = group_total;  // �׷� �Ǹŷ� ����
            group_count++;
            group_total = 0;  // �ʱ�ȭ
        }
    }

    return group_count;
}

// �ܼ� ��� �Լ� (���ĵ� ���)
void print_records(const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%-5s%3d\n", records[i].product_name, records[i].quantity);  // �̸� ���� ����, ���� ������ ����
    }
}

// ���� ��� �Լ� (���ĵ� ���)
void write_records(FILE* file, const record_t* records, int count)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%-5s%3d\n", records[i].product_name, records[i].quantity);  // �̸� ���� ����, ���� ������ ����
    }
}

// main �Լ�: ���α׷� ������
int main(void)
{
    record_t records[MAX_RECORDS];    // �Է� ������ �����
    record_t grouped[MAX_RECORDS];    // �׷�ȭ ��� �����

    // [0] �Է� ������ ������ ���� ���� ����
    if (!file_exists(INPUT_FILE_PATH))
    {
        create_sample_input_file();
    }

    // ���� ����
    FILE* input_file = fopen(INPUT_FILE_PATH, "rt");    // �б� ���
    FILE* output_file = fopen(OUTPUT_FILE_PATH, "wt");  // ���� ���

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
