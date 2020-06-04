#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


char ** letterCombinations(char * digits, int* returnSize)
{
    // define letter array    
    char *letter[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    // check input
    if (!digits || !strlen(digits)) {
        printf("invalid input!\n");
        *returnSize = 0;
        return NULL; 
    }
    
    // get letter array index, and
    // get mapping array size
    int rows = 1, cols = strlen(digits);
    int *indexes = (int *)malloc(cols * sizeof(int));
    if (!indexes) {
        printf("memory allocate error!\n");
        return NULL;
    } 
    for (int i = 0; i < cols; i++) {
        indexes[i] = (int)(digits[i] - '2');
        if (indexes[i] < 0 || indexes[i] > 7) {
            printf("expected digit is within 2 to 9, but got %c!\n", digits[i]);
            return NULL;
        }
        rows *= strlen(letter[indexes[i]]);
    }
    
    // allocate mapping array
    char **mapping = malloc(rows * sizeof(char *));
    if (!mapping) {
        printf("memory allocate error!\n");
        return NULL;
    } 
    for (int i = 0; i < rows; i++) {
        mapping[i] = malloc((cols + 1) * sizeof(char));
        if (!mapping[i]) {
            printf("memory allocate error!\n");
            return NULL;
        } if (!memset((void *)mapping[i], 0x0, (cols + 1) * sizeof(char))) {
            printf("memory setting error!\n");
            return NULL;
        }
    } 


    // set initial value
    for (int i =0; i < cols; i++) mapping[0][i] = letter[indexes[i]][0];
    
    // set values
    int start = 1;
    for (int i = cols - 1; i >= 0; i--) {
        
        // copy and setting values
        int copy_size = strlen(letter[indexes[i]]);
        for (int j = 1; j < copy_size; j ++) {
            for (int k = 0; k < start; k++) {
                if (!memcpy((void *)mapping[j * start + k], 
                            (void *)mapping[k], 
                            cols * sizeof(char))) {
                    printf("memory copy error!\n");
                    return NULL;
                }
                mapping[j * start + k][i] = letter[indexes[i]][j];
            }
        }
        start *= copy_size;
    }

    *returnSize = rows;
    return mapping;
}


void test_x0017()
{
    char a[3] = "";
    int returnSize;

    char **mapping = letterCombinations(a, &returnSize);
    for (int i = 0; i <  returnSize; i ++) printf("%s\n", mapping[i]);
    free(mapping);

}