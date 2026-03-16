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
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& heights) {
        int n = heights.size();
        vector<long long> left(n), right(n);

        // Compute left limits
        vector<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && heights[stack.back()] >= heights[i]) {
                stack.pop_back();
            }
            int prevIndex = stack.empty() ? -1 : stack.back();
            left[i] = (prevIndex == -1 ? 0 : left[prevIndex]) + (long long)(i - prevIndex) * heights[i];
            stack.push_back(i);
        }

        // Clear stack for right limits
        stack.clear();

        // Compute right limits
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && heights[stack.back()] >= heights[i]) {
                stack.pop_back();
            }
            int nextIndex = stack.empty() ? n : stack.back();
            right[i] = (nextIndex == n ? 0 : right[nextIndex]) + (long long)(nextIndex - i) * heights[i];
            stack.push_back(i);
        }

        // Calculate maximum mountain sum
        long long maxSum = 0;
        for (int i = 0; i < n; ++i) {
            long long total = left[i] + right[i] - heights[i];
            if (total > maxSum) {
                maxSum = total;
            }
        }

        return maxSum;          
    }
};
