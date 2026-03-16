// Source: https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers, k and limit. Your task is to find a non-empty subsequence of nums that:
//
//
// 	Has an alternating sum equal to k.
// 	Maximizes the product of all its numbers without the product exceeding limit.
//
//
// Return the product of the numbers in such a subsequence. If no subsequence satisfies the requirements, return -1.
//
// The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
//
// Example:
// Input: nums = [1,2,3], k = 2, limit = 10
//
// Output: 6
//
// Explanation:
//
// The subsequences with an alternating sum of 2 are:
//
//
// 	[1, 2, 3]
//
// 	
// 		Alternating Sum: 1 - 2 + 3 = 2
// 		Product: 1 * 2 * 3 = 6
// 	
// 	
// 	[2]
// 	
// 		Alternating Sum: 2
// 		Product: 2
// 	
// 	
//
//
// The maximum product within the limit is 6.
//
// Constraints:
// 1 <= nums.length <= 150
// 	0 <= nums[i] <= 12
// 	-105 <= k <= 105
// 	1 <= limit <= 5000
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Calculating the determinant of a matrix by Gauss (matrix, number, simulation, counting)
//   • When to use: When needing to compute the determinant of a square matrix, especially when Gaussian elimination is a familiar or efficient approach. It is suitable for matrices where direct cofactor expansion is computationally too expensive.
//   • Idea: This algorithm computes the determinant of a square matrix by transforming it into an upper triangular form using Gaussian elimination. The determinant is the product of diagonal elements, adjusted by a sign factor from row swaps, with O(N^3) complexity.
//   • Invariants: Before processing column 'k', all elements A[i][j] where i > j and j < k are zero.; The determinant of the current matrix, multiplied by (-1)^swaps, equals the original matrix's determinant.
//   • Tips: Track the number of row swaps to correctly determine the determinant's sign.; Pivot selection can improve numerical stability, especially with floating-point numbers.
//   • Pitfalls: Forgetting to adjust the sign after row exchanges.; Division by zero if a pivot element is zero, requiring a row swap.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxProduct(int* nums, int numsSize, int k, int limit) {
    // Step 1: Use a bitmask to generate all possible subsequences
    int maxProduct = -1;
    int totalSubsequences = 1 << numsSize; // 2^n subsequences
    for (int mask = 1; mask < totalSubsequences; mask++) {
        long long product = 1;
        int alternatingSum = 0;
        for (int i = 0; i < numsSize; i++) {
            if (mask & (1 << i)) { // If the i-th element is included in the subsequence
                if (i % 2 == 0) {
                    alternatingSum += nums[i]; // Even index
                } else {
                    alternatingSum -= nums[i]; // Odd index
                }
                product *= nums[i];
                if (product > limit) { // If product exceeds limit, break early
                    break;
                }
            }
        }
        if (alternatingSum == k && product <= limit) {
            if (product > maxProduct) {
                maxProduct = product; // Update max product if conditions are met
            }
        }
    }
    return maxProduct;
}
