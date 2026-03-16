// Source: https://leetcode.com/problems/daily-temperatures/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
//
// Example:
// Input: temperatures = [73,74,75,71,69,72,76,73]
// Output: [1,1,4,2,1,1,0,0]
//
// Constraints:
// 1 <= temperatures.length <= 105
// 	30 <= temperatures[i] <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * temperaturesSize);
    int* stack = (int*)malloc(sizeof(int) * temperaturesSize);
    int top = -1;

    for (int i = temperaturesSize - 1; i >= 0; --i) {
        while (top != -1 && temperatures[i] >= temperatures[stack[top]]) {
            --top;
        }
        if (top == -1) {
            result[i] = 0;
        } else {
            result[i] = stack[top] - i;
        }
        stack[++top] = i;
    }

    free(stack);
    *returnSize = temperaturesSize;
    return result;      
}
