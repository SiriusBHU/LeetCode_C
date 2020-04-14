#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\lib\merge_sort.h"

// using sorting and double pointer
// T(n) = O(n^2)
// S(n) = 1

// define compare func for sorting
int Compare(const void *a, const void *b)
{
    if (*((int *)a) < *((int *)b))
        return 1;
    else return 0;
}


// main body
#define MAX_ARR_SIZE 0x100
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    // check input
    if (!nums || numsSize < 3) {
        printf("invalid input!\n");
        return NULL;
    }
    
    // sort array
    MergeSort((void *)nums, numsSize, sizeof(int), Compare);
    
    // alloc memory of 2-dim array for storing
    int **arr = (int **)malloc(MAX_ARR_SIZE * sizeof(int *));
    if (!arr) {
        printf("memory allocate error!\n");
        return NULL;
    }

    // find the 3sum sub-set and store them
    int pair_count = 0;
    for (int i = 0; i < numsSize - 2 && nums[i] <= 0;) {
        for(int j = i + 1, k = numsSize - 1; j < k;) {

            // guarantee no repeated value 
            if (pair_count && nums[i] == nums[i - 1])
                break;

            int a = nums[i], b = nums[j], c = nums[k];
            
            if (nums[i] + nums[j] + nums[k] < 0) j++;
            else if (nums[i] + nums[j] + nums[k] > 0) k--;
            else {
                // alloc memory for storing
                arr[pair_count] = (int *)malloc(3 * sizeof(int));
                if (!arr[pair_count]) {
                    printf("memory allocate error!\n");
                    return NULL;
                }

                // set triple-pair value
                arr[pair_count][0] = nums[i];
                arr[pair_count][1] = nums[j];
                arr[pair_count][2] = nums[k];
                j++; k--; pair_count++;

                // guarantee no repeated value 
                while (nums[j] == nums[j + 1]) j++;
                while (nums[k] == nums[k - 1]) k--;
            }
        } 
        i++;
        // while (nums[i] == nums[i + 1]) i++;
    }

    // check pair_count and return
    *returnSize = pair_count;
    if (pair_count) return arr;
    else return NULL;
}


void test_x0015()
{
    int nums[6] = {-1, 0, 1, 2, -1, -4};
    int arr_size;
    int **arr_column_size;

    int **arr = threeSum(nums, 6, &arr_size, arr_column_size);
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < 3; j ++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}