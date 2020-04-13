//
// Created by ID4 on 2020/3/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/src/x0003_find_median_two_arr.h"

// Refer to the merge operation in MergeSorting,
// T(n) = O(n*log(n))
// S(n) = 1 or n(if we use merge array, the space complexity will be n)
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    if (!nums1 && !nums2) {
        printf("input array pointer invalid!\n");
        return -1;
    } else if (nums2 && !nums1) {
        nums1 = nums2;
        nums1Size = nums2Size;
        nums2 = NULL;
    } if (!nums2) {
        if (nums1Size % 2 == 1)
            return nums1[(int) (nums1Size / 2)];
        else
            return ((double)(nums1[(int) (nums1Size / 2)] +
                             nums1[(int) (nums1Size / 2) + 1])) / 2;
    }


    int mid_ind = (nums1Size + nums2Size) >> 1;
    int sig = (nums1Size + nums2Size) % 2 == 1 ? 1: 0;

    // merge the two sorted number array
    int i = 0, j = 0, k = 0;
    int pre = 0, post = 0;
    while (k <= mid_ind) {
        if (i < nums1Size && (nums2Size <= j || nums1[i] <= nums2[j])) {
            if (k == mid_ind - 1) pre = nums1[i];
            if (k == mid_ind) post = nums1[i];
            i++, k++;
        }

        else if (j < nums2Size && (nums1Size <= i || nums1[i] > nums2[j])) {
            if (k == mid_ind - 1) pre = nums2[j];
            if (k == mid_ind) post = nums2[j];
            j++, k++;
        }
    }

    // calculate the median
    double mid = sig
                 ? (double)post
                 : ((double)(pre + post)) / 2;

    return mid;
}


// Refer to the leet-code solution,
// According to the characteristics of median,
// it should divide the array M into two part Mi and Ma,
// satisfying elem_Mi <= elem_Ma.
// So given two sorting arrays A and B,
// we should find a position 'i' in A, and position 'j' in B
// that divide the 2 arrays into 4 parts, i. e., A_Mi, A_Ma, B_Mi, B_Ma
// satisfying:
//      1. len(A_Mi) + len(B_Mi) = len(A_Ma) + len(B_Ma),
//      2. max(B_Mi) <= min(A_Ma)   (since 'max(A_Mi) <= min(A_Ma)' always satisfies),
//      3. max(A_Mi) <= min(B_Ma)   (since 'max(B_Mi) <= min(B_Ma)' always satisfies).
// We can use Dicphoni (二分法) method to find the i.
// T(n) = O(log(n))
// S(n) = 1

double findMedianByCharacteristics(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    // check input and find a simple to return
    if (!nums1 && !nums2) {
        printf("input array pointer invalid!\n");
        return -1;
    } else if (nums2 && !nums1) {
        nums1 = nums2;
        nums1Size = nums2Size;
        nums2 = NULL;
    } if (!nums2) {
        if (nums1Size % 2 == 1)
            return nums1[(int) (nums1Size / 2)];
        else
            return ((double)(nums1[(int) (nums1Size / 2)] +
                             nums1[(int) (nums1Size / 2) + 1])) / 2;
    }

    // i in A, j in B
    // odd:     i + j = (m - i) + (n - j) + 1, or
    // even:    i + j = (m - i) + (n - j) + 1
    // j = (int)((m + n + 1) / 2) - i
    // to ensure j > 0, the i~[0, m] satisfying m <= n
    if (nums1Size > nums2Size) {
        int *temp = nums1;
        nums1 = nums2;
        nums2 = temp;

        int tmp = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tmp;
    }

    // find odd or even
    int sig = (nums1Size + nums2Size) % 2 ? 1 : 0;

    // find index i
    int i_min = 0, i_max = nums1Size;
    int i = 0, j = 0;
    while (1) {

        // calculate i, j
        i = (i_min + i_max) / 2;
        j = ((nums1Size + nums2Size + 1) / 2) - i;

        // break if satisfying
        // the boundary condition,
        if (i < 0 || i >= nums1Size) break;
        // the ending condition,
        if ((i == 0 || nums1[i - 1] <= nums2[j]) && nums2[j - 1] <= nums1[i]) break;

        // update if not satisfies
        // if i is too big
        if (i > 0 && nums1[i - 1] > nums2[j]) i_max = i - 1;
        // if i is too small
        else if (j > 0 && nums2[j - 1] > nums1[i]) i_min = i + 1;
    }

    int left = 0;
    if (i == 0) left = nums2[j - 1];
    else if (j == 0) left = nums1[i - 1];
    else left = nums1[i - 1] > nums2[j - 1] ? nums1[i - 1] : nums2[j - 1];

    if (sig)
        return (double)left;
    else {
        int right = 0;
        if (i == nums1Size) right = nums2[j];
        else if (j == nums2Size) right = nums1[i];
        else right = nums1[i] < nums2[j] ? nums1[i] : nums2[j];
        return ((double)(left + right)) / 2;
    }
}



void test_x0003()
{
    int nums1[2] = {1, 3};
    int nums2[1] = {2};
    printf("%f", findMedianByCharacteristics(nums1, 2, nums2, 1));
}