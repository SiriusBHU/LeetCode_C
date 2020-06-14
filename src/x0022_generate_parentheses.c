#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PAIRS 0x100000
void _Search(char **pairs, int *counts, int length,
             // parameters for judge interval legal
             int *sum_interval, 
             int sum_size, 
             int idx, 
             int max_interval)
{
    
    for (int i = 0; i <= max_interval && i <= idx + 1; i++) {
        
        sum_interval[idx] = i;
        if (idx == 0) {
            
            // allocate new pair memory
            int cur_row = *counts;
            pairs[cur_row] = (char *)malloc((length + 1) * sizeof(char));
            if (!pairs[cur_row]) {
                printf("memory allocate error!\n");
                *counts = 0;
                return;
            } if (!memset(pairs[cur_row], 0x0, (length + 1) * sizeof(char))) {
                printf("memory setting error!\n");
                *counts = 0;
                return;
            }
            
            // set parentheses
            int left_idx = 0;
            pairs[cur_row][left_idx] = '(';
            for (int i = 0; i < sum_size; i++) {
                left_idx = i + 1 + sum_interval[i];
                pairs[cur_row][left_idx] = '(';
            }      
            for (int idx = 0; idx < length; idx++) {
                if (!pairs[cur_row][idx])
                    pairs[cur_row][idx] = ')';
            }
            (*counts)++;
            
            /* // show result
            for (int j = 0; j < sum_size; j++)
                printf("%d ", sum_interval[j]);
            printf("%s\n", pairs[cur_row]); */

        } else {
            _Search(pairs, counts, length, 
                    sum_interval, sum_size, idx - 1, i);
        }
    }
}


char **generateParenthesis(int n, int* returnSize)
{
    // check input
    if (n <= 0) {
        printf("invalid input where n = %d < 0", n);
        *returnSize = 0;
        return NULL;
    } if (n == 1) {
        char **res = (char **)malloc(sizeof(char *));
        res[0] = (char *)malloc(3 * sizeof(char));
        res[0][0] = '('; res[0][1] = ')'; res[0][2] = 0;
        *returnSize = 1;
        return res;
    }
    
    // generate sum_interval array
    int *sum_interval = malloc((n - 1) * sizeof(int));
    if (!sum_interval) {
        printf("memory allocate error!\n");
        return NULL;
    } if (!memset(sum_interval, 0x0, (n-1) * sizeof(int))) {
        printf("memory setting error!\n");
        return NULL;
    }
    
    // generate paraentheses' pairs array
    char **pairs = (char **)malloc(MAX_PAIRS * sizeof(char *));
    if (!pairs) {
        printf("memory allocate error!\n");
        return NULL;
    }
    
    // generate pairs
    *returnSize = 0;
    _Search(pairs, returnSize, 2 * n,
            sum_interval, n - 1, n - 2, n - 1);
    
    // delete instrument variables
    if (!memset(sum_interval, 0x0, (n-1) * sizeof(int))) {
        printf("memory setting error!\n");
        return NULL;
    } free(sum_interval);
    
    // return results
    return pairs;
}


void test_x0022()
{
    int n = 3;
    int returnSize = 0;
    char **res = generateParenthesis(n, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%s\n", res[i]);
    for (int i = 0; i < returnSize; i++) free(res[i]);
    free(res);
}