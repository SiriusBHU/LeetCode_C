#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void _Search(int *sum_interval, int sum_size, int idx, int max_interval)
{   
    for (int i = 0; i <= max_interval && i <= idx + 1; i++) {
        
        sum_interval[idx] = i;
        if (idx == 0) {
            for (int j = 0; j < sum_size; j++)
                printf("%d ", sum_interval[j]);
            printf("\n");
        } else {
            _Search(sum_interval, sum_size, idx - 1, i);
            //printf("%d", 1);
        }
    }
}


char ** generateParenthesis(int n, int* returnSize){
    // n = 4
    // 4 ( ( ( (
    //   0 1 2 3
    //   ()(
    //    0 0 0
    //   第1 和第2 之间 间隔 c1  不能超过 idx2 前所有间隔不得超过 2 - 1
    //   第2 和第3 之间 间隔 c2  不能超过 idx3 前所有间隔不得超过 3 - 1
    //   c1 <= 1
    //   c1 + c2 <= 2
    //   c1 + c2 + c3 <= 3
    //   c1 + c2 + ... + cn <= n
    //   S1 <= 1;
    //   S2 <= 2;
    
    // check input
    if (n <= 0) {
        printf("invalid input where n = %d < 0", n);
        *returnSize = 0;
        return NULL;
    } if (n == 1) {
        char res[1][1] = {"()",};
        *returnSize = 1;
        return res;
    }
    
    // generate sum_interval array
    int *sum_interval = malloc((n - 1) * sizeof(int));
    memset(sum_interval, 0x0, (n-1) * sizeof(int));
    _Search(sum_interval, n - 1, n - 2, n - 1);
    
    char **res;
    *returnSize = 0;
    return res;
    
    
    
}        