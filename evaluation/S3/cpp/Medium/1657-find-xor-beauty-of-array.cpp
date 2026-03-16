// Source: https://leetcode.com/problems/find-xor-beauty-of-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// The effective value of three indices i, j, and k is defined as ((nums[i] | nums[j]) & nums[k]).
//
// The xor-beauty of the array is the XORing of the effective values of all the possible triplets of indices (i, j, k) where 0 <= i, j, k < n.
//
// Return the xor-beauty of nums.
//
// Note that:
//
//
// 	val1 | val2 is bitwise OR of val1 and val2.
// 	val1 & val2 is bitwise AND of val1 and val2.
//
// Example:
// Input: nums = [1,4]
// Output: 5
// Explanation: 
// The triplets and their corresponding effective values are listed below:
// - (0,0,0) with effective value ((1 | 1) & 1) = 1
// - (0,0,1) with effective value ((1 | 1) & 4) = 0
// - (0,1,0) with effective value ((1 | 4) & 1) = 1
// - (0,1,1) with effective value ((1 | 4) & 4) = 4
// - (1,0,0) with effective value ((4 | 1) & 1) = 1
// - (1,0,1) with effective value ((4 | 1) & 4) = 4
// - (1,1,0) with effective value ((4 | 4) & 1) = 0
// - (1,1,1) with effective value ((4 | 4) & 4) = 4 
// Xor-beauty of array will be bitwise XOR of all beauties = 1 ^ 0 ^ 1 ^ 4 ^ 1 ^ 4 ^ 0 ^ 4 = 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
//   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
//   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
//   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
//   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: Use when frequent point updates and range sum queries are needed on an array. It offers logarithmic time complexity for both operations, making it more efficient than a simple prefix sum array for dynamic data.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently calculates prefix sums and updates individual elements in an array. Both operations typically run in O(log N) time.
//   • Invariants: Each node `tree[i]` stores the sum of a specific range of elements ending at index `i`.; The length of the range summed by `tree[i]` is determined by `i & (-i)` (lowbit operation).
//   • Tips: Understand the lowbit operation and its role in navigating the tree structure.; Use 1-based indexing for simpler implementation of lowbit calculations.
//   • Pitfalls: Forgetting 1-based indexing can lead to off-by-one errors and incorrect results.; Incorrectly implementing the lowbit calculation or update/query logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int xorBeauty(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            ans ^= num;
        }
        return ans;         
    }
};
