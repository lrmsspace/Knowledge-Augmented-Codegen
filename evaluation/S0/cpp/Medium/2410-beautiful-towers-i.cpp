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
public:
    long long maximumSumOfHeights(vector<int>& heights) {
        int n = heights.size();
        vector<long long> left(n), right(n);

        // Calculate left limits
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && heights[stk.top()] > heights[i]) {
                stk.pop();
            }
            if (stk.empty()) {
                left[i] = (long long)heights[i] * (i + 1);
            } else {
                int prevIndex = stk.top();
                left[i] = left[prevIndex] + (long long)heights[i] * (i - prevIndex);
            }
            stk.push(i);
        }

        // Clear stack for right limits
        while (!stk.empty()) stk.pop();

        // Calculate right limits
        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() && heights[stk.top()] > heights[i]) {
                stk.pop();
            }
            if (stk.empty()) {
                right[i] = (long long)heights[i] * (n - i);
            } else {
                int nextIndex = stk.top();
                right[i] = right[nextIndex] + (long long)heights[i] * (nextIndex - i);
            }
            stk.push(i);
        }

        // Calculate maximum sum of mountain-shaped arrangement
        long long maxSum = 0;
        for (int i = 0; i < n; ++i) {
            long long total = left[i] + right[i] - heights[i];
            maxSum = max(maxSum, total);
        }

        return maxSum;          
    }
};
