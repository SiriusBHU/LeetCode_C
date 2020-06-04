#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "..\include\lib\merge_sort.h"



int Compare(const void *a, const void *b) {
    return (*((int *)a) - *((int *)b));
}


int Abs(const int a) {
    return a > 0 ? a : -a;
}


// main body
#define MAX_ARR_SIZE 0x100
int threeSumClosest(int* nums, int numsSize, int target)
{
    // check input
    if (!nums || numsSize < 3) {
        printf("invalid input!\n");
        return NULL;
    }
    
    // sort array
    MergeSort((void *)nums, numsSize, sizeof(int), Compare);
    

    // find the 3sum sub-set and the corresponding target
    int closest = nums[0] + nums[1] + nums[2];
    int flag = 0; // equal to target, end loop
    for (int i = 0; i < numsSize - 2;) {
        for(int j = i + 1, k = numsSize - 1; j < k;) {
                        
            if (Abs(closest - target) > 
                Abs(nums[i] + nums[j] + nums[k] - target)) {
                closest = nums[i] + nums[j] + nums[k];
            }
            
            if (nums[i] + nums[j] + nums[k] < target) j++;
            else if (nums[i] + nums[j] + nums[k] > target) k--;
            else flag = 1;
            
            if (flag) break;
        } 
        i++;
        if (flag) break;
    }

    return closest;
}

void x0016_test()
{
    int a[9] = {4,0,5,-5,3,3,0,-4,-5};
    int target = -2;
    printf("%d", threeSumClosest(a, 9, target));
}
