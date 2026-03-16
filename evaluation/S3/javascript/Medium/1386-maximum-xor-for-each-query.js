// Source: https://leetcode.com/problems/maximum-xor-for-each-query/   |   Difficulty: Medium
//
// Problem Description:
// You are given a sorted array nums of n non-negative integers and an integer maximumBit. You want to perform the following query n times:
//
//
// 	Find a non-negative integer k < 2maximumBit such that nums[0] XOR nums[1] XOR ... XOR nums[nums.length-1] XOR k is maximized. k is the answer to the ith query.
// 	Remove the last element from the current array nums.
//
//
// Return an array answer, where answer[i] is the answer to the ith query.
//
// Example:
// Input: nums = [0,1,1,3], maximumBit = 2
// Output: [0,3,2,3]
// Explanation: The queries are answered as follows:
// 1st query: nums = [0,1,1,3], k = 0 since 0 XOR 1 XOR 1 XOR 3 XOR 0 = 3.
// 2nd query: nums = [0,1,1], k = 3 since 0 XOR 1 XOR 1 XOR 3 = 3.
// 3rd query: nums = [0,1], k = 2 since 0 XOR 1 XOR 2 = 3.
// 4th query: nums = [0], k = 3 since 0 XOR 3 = 3.
//
// Constraints:
// nums.length == n
// 	1 <= n <= 105
// 	1 <= maximumBit <= 20
// 	0 <= nums[i] < 2maximumBit
// 	nums​​​ is sorted in ascending order.
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
// - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
//   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
//   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
//   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
//   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} maximumBit
 * @return {number[]}
 */
var getMaximumXor = function(nums, maximumBit) {
    const n = nums.length;
    const result = new Array(n);
    let prefixXor = 0;
    
    for (let i = 0; i < n; i++) {
        prefixXor ^= nums[i];
    }
    
    const maxVal = (1 << maximumBit) - 1;
    
    for (let i = n - 1; i >= 0; i--) {
        result[i] = prefixXor ^ maxVal;
        prefixXor ^= nums[i];
    }
    
    return result;
};
