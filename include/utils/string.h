#pragma once

static void string_reverse(char * str, int length)
{
    int start = 0;
    int end = length - 1;
    
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

static int int_to_string(int number, char * str)
{
    int i = 0;
    int isNegative = 0;

    if (number == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return 1;
    }

    if (number < 0)
    {
        isNegative = 1;
        number = -number;
    }

    while (number != 0)
    {
        int rem = number % 10;
        str[i++] = rem + '0';
        number = number / 10;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    string_reverse(str, i);

    return i;
}
