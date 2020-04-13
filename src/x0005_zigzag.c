//
// Created by ID4 on 2020/3/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/src/x0005_zigzag.h"

char *convert(char *s, int numRows)
{

    // check input
    if (!s || numRows < 1) {
        printf("invalid input!\n");
        return s;
    } else if (numRows == 1 || !(*s)) return s;

    // find the length and allocate new string
    unsigned int length = strlen(s);
    char *new_s = malloc((length + 1) * sizeof(char));
    if (!new_s) {
        printf("memory allocate error!\n");
        return s;
    } if (!memset((void *)new_s, 0x0, (length + 1) * sizeof(char))) {
        printf("memory setting error!\n");
        return s;
    }

    // set news;    n = rows * 2 - 1
    // first row    k * n
    // second row   k * n + 1, (k + 1) * n - 1
    // ...
    // last row     k * n + rows - 1

    int ind = 0;
    int cycle = numRows * 2 - 2;
    for (int row = 0; row < numRows; row++) {

        // first row or last row
        if (row == 0 || row == numRows - 1) {
            for (int k = 0; k * cycle + row < length; k++, ind++) {
                new_s[ind] = s[k * cycle + row];
            }
        }

        // middle row
        else {
            int k = 0;
            while (1) {
                if (k * cycle + row < length) {
                    new_s[ind] = s[k * cycle + row];
                    ind ++;
                } else break;

                if ((k + 1) * cycle - row < length) {
                    new_s[ind] = s[(k + 1) * cycle - row];
                    ind ++;
                } else break;
                k ++;
            }
        }
    }

    printf("%s\n", new_s);
    return new_s;
}

void test_x0005()
{
    char *s = "PAYPALISHIRING";
    convert(s, 2);
}