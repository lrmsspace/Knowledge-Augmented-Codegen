// Source: https://leetcode.com/problems/minimum-array-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and three integers k, op1, and op2.
//
// You can perform the following operations on nums:
//
//
// 	Operation 1: Choose an index i and divide nums[i] by 2, rounding up to the nearest whole number. You can perform this operation at most op1 times, and not more than once per index.
// 	Operation 2: Choose an index i and subtract k from nums[i], but only if nums[i] is greater than or equal to k. You can perform this operation at most op2 times, and not more than once per index.
//
//
// Note: Both operations can be applied to the same index, but at most once each.
//
// Return the minimum possible sum of all elements in nums after performing any number of operations.
//
// Example:
// Input: nums = [2,8,3,19,3], k = 3, op1 = 1, op2 = 1
//
// Output: 23
//
// Explanation:
//
//
// 	Apply Operation 2 to nums[1] = 8, making nums[1] = 5.
// 	Apply Operation 1 to nums[3] = 19, making nums[3] = 10.
// 	The resulting array becomes [2, 5, 3, 10, 3], which has the minimum possible sum of 23 after applying the operations.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 105
// 	0 <= k <= 105
// 	0 <= op1, op2 <= nums.length
//
// Helpful references (internal KB):
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} op1
 * @param {number} op2
 * @return {number}
 */
var minArraySum = function(nums, k, op1, op2) {
    const n = nums.length;
    const candidates = [];
    for (let i = 0; i < n; i++) {
        const op1Result = Math.ceil(nums[i] / 2);
        const op2Result = nums[i] >= k ? nums[i] - k : nums[i];
        const bestResult = Math.min(nums[i], op1Result, op2Result);
        candidates.push({ index: i, bestResult });
    }
    candidates.sort((a, b) => a.bestResult - b.bestResult);
    
    const appliedOp1 = new Set();
    const appliedOp2 = new Set();
    for (const { index, bestResult } of candidates) {
        if (bestResult < nums[index]) {
            if (bestResult === Math.ceil(nums[index] / 2) && op1 > 0 && !appliedOp1.has(index)) {
                nums[index] = bestResult;
                appliedOp1.add(index);
                op1--;
            }
            else if (bestResult === nums[index] - k && op2 > 0 && !appliedOp2.has(index)) {
                nums[index] = bestResult;
                appliedOp2.add(index);
                op2--;
            }
        }
    }
    return nums.reduce((sum, num) => sum + num, 0);
};
