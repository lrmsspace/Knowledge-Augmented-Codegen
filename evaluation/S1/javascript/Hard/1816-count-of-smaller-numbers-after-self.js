// Source: https://leetcode.com/problems/count-of-smaller-numbers-after-self/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].
//
// Example:
// Input: nums = [5,2,6,1]
// Output: [2,1,1,0]
// Explanation:
// To the right of 5 there are 2 smaller elements (2 and 1).
// To the right of 2 there is only 1 smaller element (1).
// To the right of 6 there is 1 smaller element (1).
// To the right of 1 there is 0 smaller element.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: Use when frequent point updates and range sum queries are needed on an array. It offers logarithmic time complexity for both operations, making it more efficient than a simple prefix sum array for dynamic data.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently calculates prefix sums and updates individual elements in an array. Both operations typically run in O(log N) time.
//   • Invariants: Each node `tree[i]` stores the sum of a specific range of elements ending at index `i`.; The length of the range summed by `tree[i]` is determined by `i & (-i)` (lowbit operation).
//   • Tips: Understand the lowbit operation and its role in navigating the tree structure.; Use 1-based indexing for simpler implementation of lowbit calculations.
//   • Pitfalls: Forgetting 1-based indexing can lead to off-by-one errors and incorrect results.; Incorrectly implementing the lowbit calculation or update/query logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var countSmaller = function(nums) {
    const sorted = [];
    const counts = new Array(nums.length).fill(0);

    for (let i = nums.length - 1; i >= 0; i--) {
        const index = binarySearch(sorted, nums[i]);
        counts[i] = index;
        sorted.splice(index, 0, nums[i]);
    }

    return counts;
};
