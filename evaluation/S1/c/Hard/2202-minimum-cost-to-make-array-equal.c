// Source: https://leetcode.com/problems/minimum-cost-to-make-array-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
//
// You can do the following operation any number of times:
//
//
// 	Increase or decrease any element of the array nums by 1.
//
//
// The cost of doing one operation on the ith element is cost[i].
//
// Return the minimum total cost such that all the elements of the array nums become equal.
//
// Example:
// Input: nums = [1,3,5,2], cost = [2,3,1,14]
// Output: 8
// Explanation: We can make all the elements equal to 2 in the following way:
// - Increase the 0th element one time. The cost is 2.
// - Decrease the 1st element one time. The cost is 3.
// - Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
// The total cost is 2 + 3 + 3 = 8.
// It can be shown that we cannot make the array equal with a smaller cost.
//
// Constraints:
// n == nums.length == cost.length
// 	1 <= n <= 105
// 	1 <= nums[i], cost[i] <= 106
// 	Test cases are generated in a way that the output doesn't exceed 253-1
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minCost(int* nums, int numsSize, int* cost, int costSize) {
    long long left = 1, right = 1000000; /* search space for target value */
    long long result = -1;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        /* calculate cost for making all elements equal to mid and mid+1 */
        long long costMid = 0, costMidPlusOne = 0;
        for (int i = 0; i < numsSize; ++i) {
            costMid += (long long)cost[i] * llabs(nums[i] - mid);
            costMidPlusOne += (long long)cost[i] * llabs(nums[i] - (mid + 1));
        }

        if (costMid <= costMidPlusOne) {
            result = costMid;
            right = mid - 1;
        } else {
            result = costMidPlusOne;
            left = mid + 1;
        }
    }

    return result;      
}
