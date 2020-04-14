//
// Created by ID4 on 2020/3/21.
//

#include "../include/src/x0008_str2int.h"
#include <string.h>
#include <stdio.h>

// convert single character to integer,
// if not integer, return -1
int convertChar2Int(char s)
{
    int num = (int)s - (int)('0');
    if (num >= 0 && num <= 9) {
        return num;
    } else return -1;
}

// find the start of number
char *findStart(char *str, int *sign)
{
    char *p = str;
    while (p) {

        // if char is ' ', continue
        if (*p == ' ') p++;
        // if char is '+' and its sequential char is integer
        else if (*p == '+' && -1 != convertChar2Int(*(p + 1))) {
            //
            *sign = 1;
            p++;
            break;
        } // if char is '-' and its sequential char is integer
        else if (*p == '-' && -1 != convertChar2Int(*(p + 1))) {
            *sign = 0;
            p++;
            break;
        } // if char is integer
        else if (-1 != convertChar2Int(*p)) {
            *sign = 1;
            break;
        } else {
            p = NULL;
            break;
        }
    }
    return p;
}

int myAtoi(char *str)
{

    // check input
    if (!str || !(*str)) {
        printf("invalid input");
        return 0;
    }

    // find the start and the sign of number
    int sign;
    char *p = findStart(str, &sign);

    // convert
    int num = 0;
    int tag1 = 0x7FFFFFFF / 10;
    int tag2 = ((int)0x80000000) / 10;
    while (p) {

        int o = convertChar2Int(*p);
        if (-1 != o) {

            o = sign ? o: -1 * o;
            if (num > tag1 || (num == tag1 && o > 7)) {
                num = 0x7FFFFFFF;
                break;
            } else if (num < tag2 || (num == tag2 && o < -8)) {
                num = 0x80000000;
                break;
            }
            num = num * 10 + o;
            p++;
        } else break;
    }
    return num;
}

void test_x0007()
{
    char *str = "   -33245091033233";
    printf("%d\n", myAtoi(str));
}


