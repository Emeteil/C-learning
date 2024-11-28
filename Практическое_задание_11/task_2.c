#include <stdio.h>  
  
typedef struct  
{  
    char str[5];      
    int num;  
} NumberRepr;
  
void format(NumberRepr* number)  
{ // {str = "\000\000\000\000", num = 1025}
    sprintf(number->str, "%4d", number->num);  
} // {str = "1025", num = 1025}

int main()
{  
    NumberRepr number = { .num = 1025 };  
    format(&number);  
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}  
