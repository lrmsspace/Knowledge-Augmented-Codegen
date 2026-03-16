// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k.
//
// Define a function distance(s1, s2) between two strings s1 and s2 of the same length n as:
//
//
// 	The sum of the minimum distance between s1[i] and s2[i] when the characters from 'a' to 'z' are placed in a cyclic order, for all i in the range [0, n - 1].
//
//
// For example, distance("ab", "cd") == 4, and distance("a", "z") == 1.
//
// You can change any letter of s to any other lowercase English letter, any number of times.
//
// Return a string denoting the lexicographically smallest string t you can get after some changes, such that distance(s, t) <= k.
//
// Example:
// Input: s = "zbbz", k = 3
//
// Output: "aaaz"
//
// Explanation:
//
// Change s to "aaaz". The distance between "zbbz" and "aaaz" is equal to k = 3.
//
// Constraints:
// 1 <= s.length <= 100
// 	0 <= k <= 2000
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var getSmallestString = function(s, k) {
    const n = s.length;
    const aCharCode = 'a'.charCodeAt(0);
    const zCharCode = 'z'.charCodeAt(0);
    let result = '';

    for (let i = 0; i < n; i++) {
        const currentCharCode = s.charCodeAt(i);
        const distanceToA = (currentCharCode - aCharCode + 26) % 26;
        const distanceToZ = (zCharCode - currentCharCode + 26) % 26;

        if (distanceToA <= k) {
            result += String.fromCharCode(aCharCode);
            k -= distanceToA;
        } else if (distanceToZ <= k) {
            result += String.fromCharCode(zCharCode);
            k -= distanceToZ;
        } else {
            result += s[i];
        }
    }

    return result;
};
