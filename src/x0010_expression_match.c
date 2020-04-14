//
// Created by ID4 on 2020/3/21.
//

#include "../include/src/x0010_expression_match.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// first method: Recursion
// let len(s) = n, len(p) = m
// T(n) = O((m + n)2^(n + m/2))
// S(n) = 1
bool _charMatch(char s, char p)
{
    if (s == p || (s && p == '.'))
        return true;
    else return false;
}

bool _Match(char *s, char *p)
{
    // printf("%s, %s\n", s, p);

    //check input;
    if (!*s && !*p)
        return true;
    else if ((!*s && *p && *(p + 1) != '*') || (*s && !*p))
        return false;

    // match
    if (*(p + 1) != '*') {
        if (_charMatch(*s, *p))
            return _Match(s + 1, p + 1);
        else
            return false;
    } else {
        if (_charMatch(*s, *p))
            return _Match(s + 1, p) || _Match(s, p + 2);
        else
            return _Match(s, p + 2);
    }
}

bool isMatchByRecurse(char * s, char * p)
{
    // check input
    if (!s || !p) {
        printf("invalid input!\n");
        return false;
    }

    return _Match(s, p);
}


// second & method: Dynamic Programming (DP)
// the implementation of second: Recursion
// the implementation of second: Iteration
// let len(s) = n, len(p) = m
// T(n) = O(n * m)
// S(n) = O(n * m)

// both need function
bool **boolMapCreate(unsigned int row_size,
                     unsigned int col_size)
{
    // initial row
    bool **map = (bool **)malloc(row_size * sizeof(bool *));
    if (!map) {
        printf("map memory allocate error!\n");
        return NULL;
    }

    // initial column
    for (int i = 0; i < row_size; i++) {
        map[i] = (bool *)malloc(col_size * sizeof(bool));
        if (!map[i]) {
            printf("map memory allocate error!\n");
            return NULL;
        }

//        for (int j = 0; j < col_size; j++)
//            map[i][j] = false;
        if (!memset((void *)map[i], false, col_size * sizeof(bool))) {
            printf("match map initial error!\n");
            return NULL;
        }
    }

    return map;
}

bool _charMatchDP(char s, char p)
{
    if (s == p || (s && p == '.'))
        return true;
    else return false;
}

// Recursion type
bool _MatchDP(const char *s, const char *p,
              bool **match_map, bool **check_map,
              unsigned int s_ind, unsigned int p_ind,
              unsigned int s_len, unsigned int p_len)
{
    // ending condition
    if (s_ind >= s_len && p_ind >= p_len)
        return true;
    else if ((s_ind >= s_len && p_ind != p_len && p[p_ind + 1] != '*') ||
             (s_ind != s_len && p_ind >= p_len))
        return false;

    // if not match the current letter, match
    if (!check_map[s_ind][p_ind]) {

        check_map[s_ind][p_ind] = true;
        bool cur_match = _charMatchDP(s[s_ind], p[p_ind]);
        if (p[p_ind + 1] != '*') {
            if (cur_match)
                match_map[s_ind][p_ind] = _MatchDP(s, p,
                                                   match_map, check_map,
                                                   s_ind + 1, p_ind + 1,
                                                   s_len, p_len);
            else
                match_map[s_ind][p_ind] = false;
        } else {
            if (cur_match)
                match_map[s_ind][p_ind] = _MatchDP(s, p,
                                                   match_map, check_map,
                                                   s_ind + 1, p_ind,
                                                   s_len, p_len) ||
                                          _MatchDP(s, p,
                                                   match_map, check_map,
                                                   s_ind, p_ind + 2,
                                                   s_len, p_len);
            else
                match_map[s_ind][p_ind] = _MatchDP(s, p,
                                                   match_map, check_map,
                                                   s_ind, p_ind + 2,
                                                   s_len, p_len);

        }

    } return match_map[s_ind][p_ind];
}

bool isMatchByDPRecurse(char * s, char * p)
{
    // check input
    if (!s || !p) {
        printf("invalid input!\n");
        return false;
    }

    // prepare match map for dynamic programming
    unsigned int s_len = strlen(s), p_len = strlen(p);
    bool **match_map = boolMapCreate(s_len + 1, p_len + 1);
    bool **check_map = boolMapCreate(s_len + 1, p_len + 1);

    // get result
    bool res = _MatchDP(s, p,
                        match_map, check_map,
                        0, 0,
                        s_len, p_len);

    // free the allocated memory
    for (int i = 0; i < s_len + 1; i++) {
        free(match_map[i]); free(check_map[i]);
    } free(match_map); free(check_map);

    return res;
}

// Iteration type
bool isMatchByDPIterate(char * s, char * p)
{
    // check input
    if (!s || !p) {
        printf("invalid input!\n");
        return false;
    }

    // prepare match map for dynamic programming
    unsigned int s_len = strlen(s), p_len = strlen(p);
    bool **match_map = boolMapCreate(s_len + 1, p_len + 1);
    // bool match_map[3][3] = {0};  // fix me, for test

    // fix me
    match_map[s_len][p_len] = true;
    for (int i = (int)s_len; i >= 0; i--) {
        for (int j = (int)p_len - 1; j >= 0; j--) {

            if (p[j] == '*')
                continue;

            bool cur_match = _charMatchDP(s[i], p[j]);
            if (p[j + 1] != '*') {
                if (cur_match)
                    match_map[i][j] = match_map[i + 1][j + 1];
            } else {
                if (cur_match)
                    match_map[i][j] = match_map[i][j + 2] || match_map[i + 1][j];
                else
                    match_map[i][j] = match_map[i][j + 2];
            }
        }
    }

    // get result
    bool res = match_map[0][0];

    // free the allocated memory
    for (int i = 0; i < s_len + 1; i++) {
        free(match_map[i]);
    } free(match_map);

    return res;
}



void test_x0009()
{
    char *s[7] = {"ab", "aab", "aa", "aa", "aaaaaaaaaaaaab", "ab", "mississippi"};
    char *p[7] = {".*", "c*a*b", "a*", "a", "a*a*a*a*a*a*a*a*a*a*c", ".*c", "mis*is*p*."};

    bool k[7];
    for (int i = 0; i < 7; i++) k[i] = isMatchByDPIterate(s[i], p[i]);
    printf("1");
    int m =0;
}
