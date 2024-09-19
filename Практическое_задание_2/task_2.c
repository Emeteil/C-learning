#include <stdio.h>

void main() {
    float temp;
    char temp_char;

    printf("Input temperature: ");
    scanf("%f%c", &temp, &temp_char);

    float temp_result;
    char out_char;

    if (temp_char == 'c' || temp_char == 'C')
        temp_result = (temp * 9/5) + 32, out_char = 'f';
    else if (temp_char == 'f' || temp_char == 'F')
        temp_result = (temp - 32) * 5/9, out_char = 'c';
    else {
        printf("Output error\n");
        return;
    }

    printf("Output temperature: %f%c\n", temp_result, out_char);
}
