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

class Solution {
    public long maximumSumOfHeights(int[] heights) {
        int n = heights.length;
        long[] left = new long[n];
        long[] right = new long[n];

        // Calculate left array
        Deque<Integer> stack = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            int prevIndex = stack.isEmpty() ? -1 : stack.peek();
            left[i] = (long) heights[i] * (i - prevIndex) + (prevIndex == -1 ? 0 : left[prevIndex]);
            stack.push(i);
        }

        // Clear stack for right array calculation
        stack.clear();

        // Calculate right array
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            int nextIndex = stack.isEmpty() ? n : stack.peek();
            right[i] = (long) heights[i] * (nextIndex - i) + (nextIndex == n ? 0 : right[nextIndex]);
            stack.push(i);
        }

        // Calculate maximum sum of heights
        long maxSum = 0;
        for (int i = 0; i < n; i++) {
            long total = left[i] + right[i] - heights[i];
            maxSum = Math.max(maxSum, total);
        }

        return maxSum;          
    }
}
