// Source: https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer threshold.
//
// Find any subarray of nums of length k such that every element in the subarray is greater than threshold / k.
//
// Return the size of any such subarray. If there is no such subarray, return -1.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,4,3,1], threshold = 6
// Output: 3
// Explanation: The subarray [3,4,3] has a size of 3, and every element is greater than 6 / 3 = 2.
// Note that this is the only valid subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], threshold <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int validSubarraySize(int* nums, int numsSize, int threshold) {
    int stack[numsSize];
    int top = -1;
    for (int i = 0; i <= numsSize; ++i) {
        int cur = (i == numsSize) ? 0 : nums[i];
        while (top >= 0 && nums[stack[top]] < cur) {
            int idx = stack[top--];
            int left = (top == -1) ? -1 : stack[top];
            int right = i;
            int len = right - left - 1;
            if ((long long)nums[idx] * len > threshold) {
                return len;
            }
        }
        stack[++top] = i;
    }
    return -1;      
}
