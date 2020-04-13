//
// Merge sorting (Recursion Version)
// Author: Sirius HU
// Created Date: 2020.03.05
// Modified V1:
//      Date: 2020.03.07
//      Feature: change the sorting for integer to any kind of data type
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define rank size_t

int _Merge(void *base,
           size_t elem_bytes,
           rank lo,
           rank mi,
           rank hi,
           int (*Compare)(const void *, const void *))
{
    // alloc vector head
    size_t len_head = mi - lo;
    void *vec_head = (void *)malloc(len_head * elem_bytes);
    if (!memcpy(vec_head,
                (void *)((uintptr_t)base + lo * elem_bytes),
                len_head * elem_bytes)) {
        printf("[%s]-[%d] memory copy error!\n", __func__, __LINE__);
        return -1;
    }

    // set vector tail
    size_t len_tail = hi - mi;
    void *vec_tail = (uintptr_t)base + mi * elem_bytes;

    // compare and add from little to big
    rank i = 0, j = 0, k = lo;
    while (i < len_head && j < len_tail) {
        if (Compare((uintptr_t)vec_head + i * elem_bytes, 
                    (uintptr_t)vec_tail + j * elem_bytes)) {
            if (!memcpy((uintptr_t)base + k * elem_bytes,
                        (uintptr_t)vec_head + i * elem_bytes,
                        elem_bytes)) {
                printf("[%s]-[%d] memory copy error!\n", __func__, __LINE__);
                return -1;
            } i++; k++;
        } else {
            if (!memcpy((uintptr_t)base + k * elem_bytes,
                        (uintptr_t)vec_tail + j * elem_bytes,
                        elem_bytes)) {
                printf("[%s]-[%d] memory copy error!\n", __func__, __LINE__);
                return -1;
            } j++; k++;
        }
    }

    // add the residual of vector head
    if (i < len_head) {
        if (!memcpy((uintptr_t)base + k * elem_bytes,
                    (uintptr_t)vec_head + i * elem_bytes,
                    (len_head - i) * elem_bytes)) {
            printf("[%s]-[%d] memory copy error!\n", __func__, __LINE__);
            return -1;
        }
    }

    // clear vector head and free memory
    memset((void *)vec_head, 0x0, len_head * sizeof(int));
    free(vec_head);

    return 0;
}


int _RecursiveMerge(void *base,
                    size_t elem_bytes,
                    rank lo,
                    rank hi,
                    int (*Compare)(const void *, const void *))
{
    // find middle rank
    rank mi = (lo + hi) >> 1;

    // recursion exit condition
    if (mi == lo)
        return 0;

    // recursion
    if(_RecursiveMerge(base, elem_bytes, lo, mi, Compare) ||
       _RecursiveMerge(base, elem_bytes, mi, hi, Compare))
        return -1;

    // merge
    if (_Merge(base, elem_bytes, lo, mi, hi, Compare)) {
        printf("[%s] (lo, mi, hi) = (%lu, %lu, %lu) merge error!\n",
               __func__, lo, mi, hi);
    }

    return 0;
}

// a recursion version for any kind of DS sorting
void MergeSort(void *base,
              size_t elem_num,     // data structure "size_t" means
              size_t elem_bytes,   // the maximum length of unsigned integer
              int (*Compare)(const void *, const void *)) // use the addr of func Compare
              // it is important to emphasis the structure of function pointer
              // that is "DataType (* funcName)(param_list...)
{
    // check input
    if (!base) {
        printf("[%s] invalid data base!\n", __func__);
        return;
    }

    // check if element number < 2
    if (elem_num < 2)
        return;

    // recursion of split and merge
    rank lo = 0, hi = elem_num;
    if (_RecursiveMerge(base, elem_bytes, lo, hi, Compare))
        printf("[%s] recursion of split and merge sorting error!\n", __func__);
}


