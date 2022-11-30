#include <stdio.h>

int main(void)
{
    while (1){
        char input[10], data[] = "abc";
        
        printf("Input: ");
        scanf("%s", &input);
        
        if (input[0] == 'a' && input[1] == 'b' && input[2] == 'c')
            printf("%s and %s are identical\n\n", input, data);
        else
            printf("%s and %s are not identical\n\n", input, data);
    }
}