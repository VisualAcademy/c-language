#include <stdio.h>

int main(void)
{
    int arr[3] = { 10, 20, 30 };

    printf("arr        = %p\n", arr);
    printf("&arr[0]    = %p\n", &arr[0]);
    printf("*arr       = %d\n", *arr);
    printf("*(arr + 1) = %d\n", *(arr + 1));

    return 0;
}