// Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// You can do the following operation on the array any number of times (possibly zero):
//
//
// 	Choose any index i from the array and flip all the elements from index i to the end of the array.
//
//
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
//
// Return the minimum number of operations required to make all elements in nums equal to 1.
//
// Example:
// Input: nums = [0,1,1,0,1]
//
// Output: 4
//
// Explanation:
// We can do the following operations:
//
//
// 	Choose the index i = 1. The resulting array will be nums = [0,0,0,1,0].
// 	Choose the index i = 0. The resulting array will be nums = [1,1,1,0,1].
// 	Choose the index i = 4. The resulting array will be nums = [1,1,1,0,0].
// 	Choose the index i = 3. The resulting array will be nums = [1,1,1,1,1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Bit manipulation (number, counting)
//   • When to use: When you need to manipulate individual bits within an integer, optimize space, or perform fast operations on boolean flags or small sets. It's ideal for low-level control and specific integer property checks.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators like AND, OR, XOR, NOT, and shifts. These operations allow for efficient setting, clearing, flipping, and checking of individual bits, typically with O(1) complexity per operation.
//   • Invariants: The state of any bit `i` where `i != x` is preserved during an operation on the `x`-th bit.; After `n = n | (1 << x)`, the `x`-th bit of `n` is 1.
//   • Tips: Use `1 << x` to create a mask for the x-th bit.; Understand the difference between `&`, `|`, `^`, `~`, `<<`, `>>` operators.
//   • Pitfalls: Incorrect operator precedence (e.g., `&` vs `&&`).; Off-by-one errors with bit indices (0-indexed vs 1-indexed).
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
    int minOperations(vector<int>& nums) {
        int operations = 0;
        int flipState = 0; // 0 means no flip, 1 means flipped

        for (int num : nums) {
            int effectiveValue = num ^ flipState;
            if (effectiveValue == 0) {
                operations++;
                flipState ^= 1; // Toggle the flip state
            }
        }

        return operations;          
    }
};
