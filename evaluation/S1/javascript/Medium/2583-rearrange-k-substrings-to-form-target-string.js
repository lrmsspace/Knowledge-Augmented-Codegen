// Source: https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t, both of which are anagrams of each other, and an integer k.
//
// Your task is to determine whether it is possible to split the string s into k equal-sized substrings, rearrange the substrings, and concatenate them in any order to create a new string that matches the given string t.
//
// Return true if this is possible, otherwise, return false.
//
// An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, using all the original letters exactly once.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	Split s into 2 substrings of length 2: ["ab", "cd"].
// 	Rearranging these substrings as ["cd", "ab"], and then concatenating them results in "cdab", which matches t.
//
// Constraints:
// 1 <= s.length == t.length <= 2 * 105
// 	1 <= k <= s.length
// 	s.length is divisible by k.
// 	s and t consist only of lowercase English letters.
// 	The input is generated such that s and t are anagrams of each other.
//
// Helpful references (internal KB):
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {string} t
 * @param {number} k
 * @return {boolean}
 */
var isPossibleToRearrange = function(s, t, k) {
    const n = s.length;
    const m = n / k;
    for (let i = 0; i < m; i++) {
        const freqS = new Array(26).fill(0);
        const freqT = new Array(26).fill(0);
        for (let j = 0; j < k; j++) {
            freqS[s.charCodeAt(i + j * m) - 97]++;
            freqT[t.charCodeAt(i + j * m) - 97]++;
        }
        if (!freqS.every((count, idx) => count === freqT[idx])) {
            return false;
        }
    }
    return true;
};
