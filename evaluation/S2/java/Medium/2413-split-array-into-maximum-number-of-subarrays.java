// Source: https://leetcode.com/problems/split-array-into-maximum-number-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of non-negative integers.
//
// We define the score of subarray nums[l..r] such that l <= r as nums[l] AND nums[l + 1] AND ... AND nums[r] where AND is the bitwise AND operation.
//
// Consider splitting the array into one or more subarrays such that the following conditions are satisfied:
//
//
// 	Each element of the array belongs to exactly one subarray.
// 	The sum of scores of the subarrays is the minimum possible.
//
//
// Return the maximum number of subarrays in a split that satisfies the conditions above.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,0,2,0,1,2]
// Output: 3
// Explanation: We can split the array into the following subarrays:
// - [1,0]. The score of this subarray is 1 AND 0 = 0.
// - [2,0]. The score of this subarray is 2 AND 0 = 0.
// - [1,2]. The score of this subarray is 1 AND 2 = 0.
// The sum of scores is 0 + 0 + 0 = 0, which is the minimum possible score that we can obtain.
// It can be shown that we cannot split the array into more than 3 subarrays with a total score of 0. So we return 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxSubarrays(int[] nums) {
        int count = 0;
        int currentAnd = -1; // Start with all bits set (for non-negative integers)

        for (int num : nums) {
            if (currentAnd == -1) {
                currentAnd = num; // Initialize with the first number
            } else {
                currentAnd &= num; // Update the AND with the current number
            }

            if (currentAnd == 0) {
                count++; // We can split here since the score is minimized
                currentAnd = -1; // Reset for the next subarray
            }
        }

        return count;           
    }
}
