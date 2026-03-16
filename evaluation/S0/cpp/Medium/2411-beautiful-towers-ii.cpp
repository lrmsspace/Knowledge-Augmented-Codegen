// Source: https://leetcode.com/problems/beautiful-towers-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array maxHeights of n integers.
//
// You are tasked with building n towers in the coordinate line. The ith tower is built at coordinate i and has a height of heights[i].
//
// A configuration of towers is beautiful if the following conditions hold:
//
//
// 	1 <= heights[i] <= maxHeights[i]
// 	heights is a mountain array.
//
//
// Array heights is a mountain if there exists an index i such that:
//
//
// 	For all 0 < j <= i, heights[j - 1] <= heights[j]
// 	For all i <= k < n - 1, heights[k + 1] <= heights[k]
//
//
// Return the maximum possible sum of heights of a beautiful configuration of towers.
//
// Example:
// Input: maxHeights = [5,3,4,1,1]
// Output: 13
// Explanation: One beautiful configuration with a maximum sum is heights = [5,3,3,1,1]. This configuration is beautiful since:
// - 1 <= heights[i] <= maxHeights[i]  
// - heights is a mountain of peak i = 0.
// It can be shown that there exists no other beautiful configuration with a sum of heights greater than 13.
//
// Constraints:
// 1 <= n == maxHeights.length <= 105
// 	1 <= maxHeights[i] <= 109
//

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        int n = maxHeights.size();
        vector<long long> left(n), right(n);
        stack<int> stk;

        // Calculate left limits
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && maxHeights[stk.top()] > maxHeights[i]) {
                stk.pop();
            }
            left[i] = stk.empty() ? (long long)maxHeights[i] * (i + 1)
                                 : left[stk.top()] + (long long)maxHeights[i] * (i - stk.top());
            stk.push(i);
        }

        // Clear stack for right limits calculation
        while (!stk.empty()) stk.pop();

        // Calculate right limits
        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() && maxHeights[stk.top()] > maxHeights[i]) {
                stk.pop();
            }
            right[i] = stk.empty() ? (long long)maxHeights[i] * (n - i)
                                  : right[stk.top()] + (long long)maxHeights[i] * (stk.top() - i);
            stk.push(i);
        }

        // Find maximum sum of heights
        long long maxSum = 0;
        for (int i = 0; i < n; ++i) {
            maxSum = max(maxSum, left[i] + right[i] - maxHeights[i]);
        }

        return maxSum;          
    }
};
