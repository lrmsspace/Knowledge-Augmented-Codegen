// Source: https://leetcode.com/problems/find-mirror-score-of-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// We define the mirror of a letter in the English alphabet as its corresponding letter when the alphabet is reversed. For example, the mirror of 'a' is 'z', and the mirror of 'y' is 'b'.
//
// Initially, all characters in the string s are unmarked.
//
// You start with a score of 0, and you perform the following process on the string s:
//
//
// 	Iterate through the string from left to right.
// 	At each index i, find the closest unmarked index j such that j < i and s[j] is the mirror of s[i]. Then, mark both indices i and j, and add the value i - j to the total score.
// 	If no such index j exists for the index i, move on to the next index without making any changes.
//
//
// Return the total score at the end of the process.
//
// Example:
// Input: s = "aczzx"
//
// Output: 5
//
// Explanation:
//
//
// 	i = 0. There is no index j that satisfies the conditions, so we skip.
// 	i = 1. There is no index j that satisfies the conditions, so we skip.
// 	i = 2. The closest index j that satisfies the conditions is j = 0, so we mark both indices 0 and 2, and then add 2 - 0 = 2 to the score.
// 	i = 3. There is no index j that satisfies the conditions, so we skip.
// 	i = 4. The closest index j that satisfies the conditions is j = 1, so we mark both indices 1 and 4, and then add 4 - 1 = 3 to the score.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var calculateScore = function(s) {
    const n = s.length;
    const mirror = new Array(26);
    for (let i = 0; i < 26; i++) {
        mirror[i] = -1;
    }
    let score = 0;
    for (let i = 0; i < n; i++) {
        const c = s.charCodeAt(i) - 'a'.charCodeAt(0);
        if (mirror[c] !== -1) {
            score += (i - mirror[c]);
        } else {
            mirror[c] = i;
        }
    }
    return score;
};
