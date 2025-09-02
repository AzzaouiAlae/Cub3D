#include "ft_func.h"

int ft_count_char(char *str, char ch)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str && str[i])
    {
        if (str[i] == ch)
            count++;
        i++;
    }
    return count;
} 
