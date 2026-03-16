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
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        int n = maxHeights.size();
        vector<long long> left(n), right(n);

        // Compute left limits
        vector<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && maxHeights[stack.back()] >= maxHeights[i]) {
                stack.pop_back();
            }
            int prevIdx = stack.empty() ? -1 : stack.back();
            left[i] = (prevIdx == -1 ? (long long)maxHeights[i] * (i + 1)
                                    : left[prevIdx] + (long long)maxHeights[i] * (i - prevIdx));
            stack.push_back(i);
        }

        // Clear stack for right limits
        stack.clear();

        // Compute right limits
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && maxHeights[stack.back()] >= maxHeights[i]) {
                stack.pop_back();
            }
            int nextIdx = stack.empty() ? n : stack.back();
            right[i] = (nextIdx == n ? (long long)maxHeights[i] * (n - i)
                                     : right[nextIdx] + (long long)maxHeights[i] * (nextIdx - i));
            stack.push_back(i);
        }

        // Calculate maximum sum of heights
        long long maxSum = 0;
        for (int i = 0; i < n; ++i) {
            long long totalHeight = left[i] + right[i] - maxHeights[i];
            if (totalHeight > maxSum) {
                maxSum = totalHeight;
            }
        }

        return maxSum;          
    }
};
