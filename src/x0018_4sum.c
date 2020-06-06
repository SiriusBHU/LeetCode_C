#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// using sorting and double pointer
// T(n) = O(n^3)
// S(n) = 1

// define compare func for sorting
int Compare(const void *a, const void *b)
{
    if (*((int *)a) < *((int *)b))
        return -1;
    else return 1;
}

#define MAX_ARR_SIZE 0x10000
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){
    
    // check input
    if (!nums || numsSize < 4) {
        printf("invalid input!\n");
        *returnSize = 0;
        return NULL;
    }
    
    // sort array
    qsort((void *)nums, numsSize, sizeof(int), Compare);
    
    // alloc memory of 2-dim array for storing
    int **arr = (int **)malloc(MAX_ARR_SIZE * sizeof(int *));
    if (!arr) {
        printf("memory allocate error!\n");
        return NULL;
    }

    // find the 4sum sub-set and store them
    int pair_count = 0;
    for (int i = 0; i < numsSize - 3; i ++) {

        // guarantee no repeated value 
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        // set loop ending condition
        if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
        if (nums[i] + nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3] < target) continue;
        
        for(int j = i + 1; j < numsSize - 2; j ++) {
            // guarantee no repeated value 
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            for (int k = j + 1, l = numsSize - 1; k < l;) {
                if (nums[i] + nums[j] + nums[k] + nums[l] < target) k++;
                else if (nums[i] + nums[j] + nums[k] + nums[l] > target) l--;
                else {
                    // alloc memory for storing
                    arr[pair_count] = (int *)malloc(4 * sizeof(int));
                    if (!arr[pair_count]) {
                        printf("memory allocate error!\n");
                        return NULL;
                    }

                    // set triple-pair value
                    arr[pair_count][0] = nums[i];
                    arr[pair_count][1] = nums[j];
                    arr[pair_count][2] = nums[k];
                    arr[pair_count][3] = nums[l];
                    pair_count++;

                    // guarantee no repeated value 
                    while (k < l && nums[k] == nums[k + 1]) k++;
                    while (k < l && nums[l] == nums[l - 1]) l--;
                    k++; l--;
                }
            }
        } 
    }

    // check pair_count and return
    if (pair_count) {
        *returnSize = pair_count;
        *returnColumnSizes = malloc(pair_count * sizeof(int));
        for (int i = 0; i < pair_count; i++) (*returnColumnSizes)[i] = 4;
        return arr;
    }
    else {
        *returnSize = 0;
        return NULL;
    }
}

void test_x0018()
{
    int nums[8] = {1, 4, 2, 8, 0, -11, 4, 6};
    int target = -1;
    int returnSize, *returnColumnSizes;
    int **res;

    res = fourSum(nums, 8, target, &returnSize, &returnColumnSizes);
}