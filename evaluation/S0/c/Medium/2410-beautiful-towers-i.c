// Source: https://leetcode.com/problems/beautiful-towers-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array heights of n integers representing the number of bricks in n consecutive towers. Your task is to remove some bricks to form a mountain-shaped tower arrangement. In this arrangement, the tower heights are non-decreasing, reaching a maximum peak value with one or multiple consecutive towers and then non-increasing.
//
// Return the maximum possible sum of heights of a mountain-shaped tower arrangement.
//
// Example:
// Input: heights = [5,3,4,1,1]
//
// Output: 13
//
// Explanation:
//
// We remove some bricks to make heights = [5,3,3,1,1], the peak is at index 0.
//
// Constraints:
// 1 <= n == heights.length <= 103
// 	1 <= heights[i] <= 109
//

long long maximumSumOfHeights(int* heights, int heightsSize) {
    int n = heightsSize;
    long long maxSum = 0;

    for (int peak = 0; peak < n; peak++) {
        long long currentSum = heights[peak];
        int minHeight = heights[peak];

        // Calculate left side
        for (int i = peak - 1; i >= 0; i--) {
            minHeight = (heights[i] < minHeight) ? heights[i] : minHeight;
            currentSum += minHeight;
        }

        minHeight = heights[peak];

        // Calculate right side
        for (int i = peak + 1; i < n; i++) {
            minHeight = (heights[i] < minHeight) ? heights[i] : minHeight;
            currentSum += minHeight;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    return maxSum;      
}
