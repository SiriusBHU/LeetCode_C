//
// Created by ID4 on 2020/3/10.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/src/x0005_palindromic_substring.h"



// center search
# define rank unsigned long
char * longestPalindrome(char * s)
{
    // check input
    if (!s) {
        printf("invalid input!\n");
        return NULL;
    }
    rank len = strlen(s);
    if (!len) return s;

    // malloc radius array
    rank *r_odd = (rank *)malloc(len * sizeof(rank));
    rank *r_even = (rank *)malloc((len - 1) * sizeof(rank));
    if (!r_odd || ! r_even) {
        printf("memory allocate error!\n");
        return NULL;
    } if (!memset((void *)r_odd, 0x00, len * sizeof(rank)) ||
          !memset((void *)r_even, 0x00, (len - 1) * sizeof(rank))) {
        printf("memory setting error!\n");
        return NULL;
    }

    // find radius
    for (int i = 0; i < len; i++) {
        for (int j = 0; i - j >= 0 && i + j < len; j++) {
            if (s[i - j] == s[i + j]) r_odd[i] += 1;
            else break;
        }
        for (int j = 0; i - j >= 0 && i + j + 1 < len; j++) {
            if (i + j + 1 < len && s[i - j] == s[i + j + 1]) r_even[i] += 1;
            else break;
        }
    }

    // find maximum of radius and center
    rank ind = 0, max_r = 0, is_even = 0;
    for (rank i = 0; i < len; i++) {
        if (r_odd[i] > max_r) {
            ind = i;
            max_r = r_odd[i];
        }
    } for (rank i = 0; i < len - 1; i++) {
        if (r_even[i] >= max_r) {
            ind = i;
            max_r = r_even[i];
            is_even = 1;
        }
    }

    // calculate start and range
    rank start = ind - max_r + 1;
    rank range = 2 * max_r;
    if (is_even) {
        range = 2 * max_r + 1;
    }

    // return sub-string;
    char *sub_s = (char *)malloc(range * sizeof(char));
    if (!sub_s) {
        printf("memory allocate error!\n");
        return NULL;
    } if (!memset((void *)sub_s, 0x0, range * sizeof(char))) {
        printf("memory setting error!\n");
        return NULL;
    } if (!memcpy((void *)sub_s, (void *)(s + start), (range - 1) * sizeof(char))) {
        printf("memory copy error!\n");
        return NULL;
    }

    return sub_s;

}


char * longestPalindromeByManacher(char * s)
{
    // check input
    if (!s) {
        printf("invalid input!\n");
        return NULL;
    }
    int len = (int)strlen(s);
    if (!len) return s;

    // create string to expand by '#', and radius array
    int len_expand = 2 * len + 1;
    int *radius = malloc(len_expand * sizeof(int));
    char *s_expand = malloc((len_expand + 1) * sizeof(char));
    if (!s_expand || !radius) {
        printf("memory allocate error!\n");
        return NULL;
    } if (!memset((void *)s_expand, 0x0, (len_expand + 1) * sizeof(char)) ||
          !memset((void *)radius, 0x0, len_expand * sizeof(char))) {
        printf("memory set error!\n");
        return NULL;
    }

    // expand
    for (int i = 0; i < len_expand; i++) {
        if (i % 2) s_expand[i] = s[i / 2];
        else s_expand[i] = '#';
    }

    // calculate radius
    int sym_ind = 0, sym_r = 1;
    radius[0] = 1;
    for (int i = 1; i < len_expand; i++) {

        // judge whether the i point within the range of sym_ind point
        if (i <= sym_ind + sym_r - 1) {
            // the center is sym_ind, calculate the symmetry point _i of i
            int _i = 2 * sym_ind - i;

            // if the range of _i within the range of sym_ind,
            // radius of i must be the same as that of _i
            if (_i - radius[_i] >= sym_ind - sym_r) radius[i] = radius[_i];
            else {
                radius[i] = sym_ind + sym_r - i;
                for (int j = radius[i]; i + j < len_expand; j++) {
                    if (s_expand[i - j] == s_expand[i + j]) radius[i] ++;
                    else break;
                }
            }
        } else {
            radius[i] = 1;
            for (int j = 1; i + j < len_expand; j++) {
                if (i - j >= 0 && s_expand[i - j] == s_expand[i + j]) radius[i] ++;
                else break;
            }
        }
    }

    /*
    // for testing
    for (int i = 0; i < len_expand; i++) printf("%3d", i);
    printf("\n");

    for (int i = 0; i < len_expand; i++) printf("  %c", s_expand[i]);
    printf("\n");

    for (int i = 0; i < len_expand; i++) printf("%3d", radius[i]);
    printf("\n");
    */

    // find length and start of sub-string
    int length = 0, start = 0;
    for (int i = 0; i < len_expand; i++) {
        if (radius[i] - 1 > length) {
            length = radius[i] - 1;
            start = (i - length) / 2;
        }
    }

    // return sub-string;
    char *sub_s = (char *)malloc((length + 1) * sizeof(char));
    if (!sub_s) {
        printf("memory allocate error!\n");
        return NULL;
    } if (!memset((void *)sub_s, 0x0, (length + 1) * sizeof(char))) {
        printf("memory setting error!\n");
        return NULL;
    } if (!memcpy((void *)sub_s, (void *)(s + start), length * sizeof(char))) {
        printf("memory copy error!\n");
        return NULL;
    }
    return sub_s;
}


void test_x0004()
{
    char *s = "babad"; // "babad", "cbbd", "aaaaaaa", "abaaba", "babcbabcbaccba"
    printf("%s\n", longestPalindromeByManacher(s));
}
