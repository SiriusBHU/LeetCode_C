#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int maxArea(int* height, int heightSize)
{       
    // check input
    if (!height || heightSize < 1) {
        printf("input invalid!\n");
        return -1;
    }
    
    // searching
    int max_vol = 0;
    for (int start = 0, end = heightSize - 1; start != end;) {
        
        int cur_h = height[start] < height[end] ? height[start] : height[end];
        int cur_vol = (end - start) * cur_h;
        max_vol = max_vol > cur_vol ? max_vol : cur_vol;
        
        if (height[start] < height[end]) start ++;
        else end --;
        
    }
    
    return max_vol;
    
}

void test_000A()
{
    int height[9] = {1,8,6,2,5,4,8,3,7};
    int vol = maxArea(height, 9);
    printf("%d\n", vol);
}