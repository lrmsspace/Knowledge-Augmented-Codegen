// Source: https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the bitwise AND operator.
//
// Return the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
//
// Example:
// Input: nums = [3,5,3,2,7], k = 2
// Output: 3
// Explanation: Let's do the following operations:
// 1. Replace nums[0] and nums[1] with (nums[0] & nums[1]) so that nums becomes equal to [1,3,2,7].
// 2. Replace nums[2] and nums[3] with (nums[2] & nums[3]) so that nums becomes equal to [1,3,2].
// The bitwise-or of the final array is 3.
// It can be shown that 3 is the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < 230
// 	0 <= k < nums.length
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Bit manipulation (number, simulation)
//   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
//   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
//   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
//   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
 * @return {number}
 */
var minOrAfterOperations = function(nums, k) {
    let low = 0;
    let high = 0;
    for (const num of nums) {
        high |= num;
    }

    const n = nums.length;

    const check = (mid) => {
        let count = 0;
        for (let i = 0; i < n - 1; i++) {
            if ((nums[i] & nums[i + 1]) <= mid) {
                count++;
                i++; // Skip the next element as it's merged
            }
        }
        return count >= k;
    };

    while (low < high) {
        const mid = low + Math.floor((high - low) / 2);
        if (check(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return low;
};
