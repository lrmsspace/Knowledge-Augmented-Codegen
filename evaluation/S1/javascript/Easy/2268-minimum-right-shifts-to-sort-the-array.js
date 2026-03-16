// Source: https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of length n containing distinct positive integers. Return the minimum number of right shifts required to sort nums and -1 if this is not possible.
//
// A right shift is defined as shifting the element at index i to index (i + 1) % n, for all indices.
//
// Example:
// Input: nums = [3,4,5,1,2]
// Output: 2
// Explanation: 
// After the first right shift, nums = [2,3,4,5,1].
// After the second right shift, nums = [1,2,3,4,5].
// Now nums is sorted; therefore the answer is 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	nums contains distinct integers.
//
// Helpful references (internal KB):
// - Shell Sort (array, shell-sort)
//   • When to use: Use when an in-place comparison sort is needed for medium-sized arrays, offering better performance than simple quadratic sorts. It is particularly effective when the data is already partially sorted.
//   • Idea: Shell Sort is an in-place comparison sort that improves upon insertion sort by allowing the exchange of items that are far apart. It sorts elements at a certain 'gap' distance, then progressively reduces the gap, leading to an O(N log N) to O(N^2) time complexity depending on the gap sequence.
//   • Invariants: For any k in [0, gap-1], the subsequence arr[k], arr[k+gap], arr[k+2*gap], ... is sorted up to the current element being processed by the inner insertion sort.; The gap value is always a positive integer and strictly decreases in each outer loop iteration.
//   • Tips: Choose an effective gap sequence (e.g., Knuth's, Sedgewick's) for optimal performance.; It is an in-place sorting algorithm, requiring O(1) auxiliary space.
//   • Pitfalls: Performance heavily depends on the chosen gap sequence; a poor sequence can lead to O(N^2) complexity.; It is not a stable sort, meaning the relative order of equal elements is not preserved.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumRightShifts = function(nums) {
    const n = nums.length;
    let pivot = -1;
    for (let i = 1; i < n; i++) {
        if (nums[i] < nums[i - 1]) {
            if (pivot !== -1) {
                return -1; // More than one pivot found
            }
            pivot = i;
        }
    }
    if (pivot === -1) {
        return 0; // Already sorted
    }
    // Check if the array is sorted after the pivot
    for (let i = pivot + 1; i < n; i++) {
        if (nums[i] < nums[i - 1]) {
            return -1; // Not sorted after pivot
        }
    }
    // Check the wrap-around condition
    if (nums[0] < nums[n - 1]) {
        return -1; // Not sorted in wrap-around
    }
    return n - pivot;
};
