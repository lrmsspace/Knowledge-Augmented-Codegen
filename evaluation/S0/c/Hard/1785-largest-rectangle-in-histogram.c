// Source: https://leetcode.com/problems/largest-rectangle-in-histogram/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
//
// Example:
// Input: heights = [2,1,5,6,2,3]
// Output: 10
// Explanation: The above is a histogram where width of each bar is 1.
// The largest rectangle is shown in the red area, which has an area = 10 units.
//
// Constraints:
// 1 <= heights.length <= 105
// 	0 <= heights[i] <= 104
//

int largestRectangleArea(int* heights, int heightsSize) {
    if (heightsSize == 0) return 0;

    int *stack = (int*)malloc((heightsSize + 1) * sizeof(int));
    if (!stack) return 0;
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= heightsSize; ++i) {
        int h = (i == heightsSize) ? 0 : heights[i];
        while (top != -1 && heights[stack[top]] >= h) {
            int height = heights[stack[top--]];
            int width = (top == -1) ? i : i - stack[top] - 1;
            int area = height * width;
            if (area > maxArea) maxArea = area;
        }
        stack[++top] = i;
    }

    free(stack);
    return maxArea;     
}
