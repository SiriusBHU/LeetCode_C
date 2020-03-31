//
// Created by ID4 on 2020/3/6.
//

#ifndef LEETCODE_C_MERGE_SORT_H
#define LEETCODE_C_MERGE_SORT_H
#endif //LEETCODE_C_MERGE_SORT_H

#include <stdio.h>

void MergeSort(void *base,
               size_t elem_num,     // data structure "size_t" means
               size_t elem_bytes,   // the maximum length of unsigned integer
               int (*Compare)(const void *, const void *));