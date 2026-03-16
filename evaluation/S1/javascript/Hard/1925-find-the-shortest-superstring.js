// Source: https://leetcode.com/problems/find-the-shortest-superstring/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.
//
// You may assume that no string in words is a substring of another string in words.
//
// Example:
// Input: words = ["alex","loves","leetcode"]
// Output: "alexlovesleetcode"
// Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
//
// Constraints:
// 1 <= words.length <= 12
// 	1 <= words[i].length <= 20
// 	words[i] consists of lowercase English letters.
// 	All the strings of words are unique.
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} words
 * @return {string}
 */
var shortestSuperstring = function(words) {
    const n = words.length;
    const overlap = Array.from({ length: n }, () => new Array(n).fill(0));

    // Calculate the overlap between pairs of words
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                const minLen = Math.min(words[i].length, words[j].length);
                for (let k = minLen; k > 0; k--) {
                    if (words[i].endsWith(words[j].substring(0, k))) {
                        overlap[i][j] = k;
                        break;
                    }
                }
            }
        }
    }

    const dp = new Array(1 << n).fill(null).map(() => new Array(n).fill(''));
    const parent = new Array(1 << n).fill(null).map(() => new Array(n).fill(-1));

    for (let mask = 1; mask < (1 << n); mask++) {
        for (let i = 0; i < n; i++) {
            if ((mask & (1 << i)) === 0) continue;

            const prevMask = mask ^ (1 << i);
            if (prevMask === 0) {
                dp[mask][i] = words[i];
            } else {
                for (let j = 0; j < n; j++) {
                    if ((prevMask & (1 << j)) === 0) continue;

                    const candidate = dp[prevMask][j] + words[i].substring(overlap[j][i]);
                    if (!dp[mask][i] || candidate.length < dp[mask][i].length) {
                        dp[mask][i] = candidate;
                        parent[mask][i] = j;
                    }
                }
            }
        }
    }

    let minIndex = 0;
    let minString = dp[(1 << n) - 1][0];
    for (let i = 1; i < n; i++) {
        if (dp[(1 << n) - 1][i].length < minString.length) {
            minString = dp[(1 << n) - 1][i];
            minIndex = i;
        }
    }

    return minString;
};
