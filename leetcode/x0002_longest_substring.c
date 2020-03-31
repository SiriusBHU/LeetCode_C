//
// Created by ID4 on 2020/3/9.
// Given a string, find the length of the longest
// substring without repeating characters.

#include <string.h>
#include <stdio.h>
#include "x0002_longest_substring.h"


#define LETTER_HASH_SIZE 0x100

int LetterHash(char letter)
{
    int ind = (int)(letter - 'a') % LETTER_HASH_SIZE;
    return ind >= 0 ? ind : ind + LETTER_HASH_SIZE;
}

void LetterHashInsert(int *map, char letter, int ind)
{
    map[LetterHash(letter)] = ind;
}

int LetterHashFind(int *map, char letter)
{
    return map[LetterHash(letter)];
}

int lengthOfLongestSubstring(char *s)
{
    // construct hash map
    int map[LETTER_HASH_SIZE] = {0};
    if (!memset((void *)map, 0x0, LETTER_HASH_SIZE * sizeof(int))) {
        printf("memory set error");
        return -1;
    }

    // preparation
    int cur_start = 1, max_len = 0;
    char *p = s;

    // find sub-string
    for (int ind = 1; *p!='\0'; p++, ind++) {

        // check if the letter is repeated
        int p_ind = LetterHashFind(map, *p);
        if (p_ind >= cur_start)
            cur_start = p_ind + 1;

        // find the maximum of length
        max_len = ind - cur_start + 1 > max_len
                  ? ind - cur_start + 1
                  : max_len;

        // update the hash-map
        LetterHashInsert(map, *p, ind);
    }
    return max_len;
}

void test_x0002()
{
    char *s = "abcabcbb"; // "abcabcbb", "bbbbbbb", "pwwkew" "tmmzuxt"
    printf("%d\n", lengthOfLongestSubstring(s));

}
