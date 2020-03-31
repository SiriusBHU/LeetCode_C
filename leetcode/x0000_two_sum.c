//
// Created by ID4 on 2020/3/6.
// Q1: Two Sum
// Given an array of integers, return indices of the two
// numbers such that they add up to a specific target.
// You may assume that each input would have exactly one
// solution, and you may not use the same element twice.
//
// each input would have one exact solution
//      have solution
//      only one solution
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/merge_sort.h"


// a Merge-Sort version,
// T(n) = O(n*log(n)),
// S(n) = O(n).
struct Elem {
    int value;
    int index;
};

int Compare(const void *a, const void*b)
{
    return (int)(*(struct Elem *)a).value - (*(struct Elem *)b).value <= 0 ? 1: 0;
}

int *twoSum(const int *nums, int numsSize, int target, int *returnSize)
{
    // judge ret
    int *ret = (int *)malloc(2 * sizeof(int));
    if (!memset((void *)ret, 0xFF, 2 * sizeof(int))) {
        printf("ret memory is not allocated!\n");
        return ret;
    }

    // judge input nums
    if (!nums) {
        printf("input array is NULL!\n");
        return ret;
    }

    // create an element array
    struct Elem *elem = malloc(numsSize * sizeof(struct Elem));
    if (!elem) {
        printf("memory allocate error!\n");
        return ret;
    }
    for (int i=0; i<numsSize; i++) {
        elem[i].value = nums[i];
        elem[i].index = i;
    }

    // sorting
    MergeSort((void *)elem, numsSize, sizeof(struct Elem), Compare);

    // find the value pair
    int head = 0, tail = numsSize - 1;
    int is_pair = 0;
    while (head != tail) {

        if (elem[head].value + elem[tail].value < target)
            head++;
        else if (elem[head].value + elem[tail].value > target)
            tail--;
        else {
            ret[0] = elem[head].index;
            ret[1] = elem[tail].index;
            is_pair = 1;
            *returnSize = 2;
            break;
        }
    }

    // free num_sort
    memset((void *)elem, 0x0, numsSize * sizeof(struct Elem));
    free(elem);

    // if there is no such pair, warning, return
    if (!is_pair)
        printf("there is no such pair (a, b) that a + b = %d!\n", target);

    return ret;
}


// a simplified version of hash
// considering that there is no duplicated element,
// so we can use a single "mod" func to match the key-value pair.
// We use hash-func to calculate the index of "key",
// then insert the value to the hash-table[index]. Here, key=value
// T(n) = O(n),
// S(n) = O(HASH_SIZE).
#define HASH_SIZE 0x10000

int HashFunc(int key)
{
    int ind = key % HASH_SIZE;
    return ind < 0 ? ind + HASH_SIZE : ind;
}

void HashInsert(int *hash_table, int key, int value)
{
    int ind = HashFunc(key);
    hash_table[ind] = value;
}

int HashFind(int *hash_table, int key)
{
    int ind = HashFunc(key);
    return hash_table[ind];
}

int *twoSumHash(const int *nums, int numsSize, int target, int *returnSize)
{
    // judge ret
    int *ret = (int *)malloc(2 * sizeof(int));
    if (!memset((void *)ret, 0xFF, 2 * sizeof(int))) {
        printf("ret memory is not allocated!\n");
        return ret;
    }

    // judge input nums
    if (!nums) {
        printf("input array is NULL!\n");
        return ret;
    }

    // create an hash table
    int hash_tab[HASH_SIZE] = {0};

    // hash and search
    int is_pair = 0;
    for (int i=0; i<numsSize; i++) {

        // index_p1 means index + 1,
        // here to set that because the initial value of hash_tab may be 0,
        // we need index-value >= 1 to judge,
        // whether the num has been hashed and stored or not.
        int index_p1 = HashFind(hash_tab, target - nums[i]);
        if (index_p1) {
            ret[0] = index_p1 - 1;
            ret[1] = i;
            is_pair = 1;
            *returnSize = 2;
            break;
        }
        HashInsert(hash_tab, nums[i], i + 1);
    }

    // if there is no such pair, warning, return
    if (!is_pair)
        printf("there is no such pair (a, b) that a + b = %d!\n", target);

    return ret;
}

void test_x0000()
{
    int nums[4] = {0, 3, 4, 0};
    int ind_size, *ind;
    ind = twoSumHash(nums, 4, 0, &ind_size);

    if (ind[0] == -1)
        printf("search error!\n");
    else
        printf("%d-(%d, %d): (%d, %d)\n",
               ind_size,
               ind[0], ind[1],
               nums[ind[0]], nums[ind[1]]);
}
