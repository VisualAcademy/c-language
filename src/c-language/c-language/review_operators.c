#include <stdio.h>

int main(void)
{
    int a = 5;  // Ã¹ ¹øÂ° Á¤¼ö º¯¼ö
    int b = 3;  // µÎ ¹øÂ° Á¤¼ö º¯¼ö

    int sum = a + b;  // µ¡¼À
    int diff = a - b;  // »¬¼À
    int product = a * b;  // °ö¼À
    int quotient = a / b;  // ³ª´°¼À
    int remainder = a % b;  // ³ª¸ÓÁö ¿¬»ê

    printf("ÇÕ: %d\n", sum);
    printf("Â÷: %d\n", diff);
    printf("°ö: %d\n", product);
    printf("¸ò: %d\n", quotient);
    printf("³ª¸ÓÁö: %d\n", remainder);

    return 0;
}