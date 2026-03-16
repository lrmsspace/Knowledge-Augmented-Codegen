// Source: https://leetcode.com/problems/shortest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. You can convert s to a palindrome by adding characters in front of it.
//
// Return the shortest palindrome you can find by performing this transformation.
//
// Example:
// Input: s = "aacecaaa"
// Output: "aaacecaaa"
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of lowercase English letters only.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var shortestPalindrome = function(s) {
    //
    // Approach: Manacher's Algorithm
    // - We can use Manacher's algorithm to find the longest palindromic prefix of the string. Once we have the length of this prefix, we can determine the characters that need to be added in front of the string to make it a palindrome.
    // - Steps:
    //   1. Preprocess the string by inserting a special character (e.g., '#') between each character and at the beginning and end to handle even-length palindromes uniformly.
    //   2. Use Manacher's algorithm to find the longest palindromic substring that starts at the beginning of the original string.
    //   3. The length of this longest palindromic prefix will help us determine the characters that need to be added in front of the string.
    // - Time Complexity: O(N) due to Manacher's algorithm.
        
    // Preprocess the string
    const preprocess = (s) => {
        let t = '#';
        for (let char of s) {
            t += char + '#';
        }
        return t;
    };

    const t = preprocess(s);
    const n = t.length;
    const d = new Array(n).fill(0);
    let l = 0, r = -1;
    for (let i = 0; i < n; i++) {
        let k = (i > r) ? 1 : Math.min(d[l + r - i], r - i + 1);
        while (i + k < n && i - k >= 0 && t[i + k] === t[i - k]) {
            k++;
        }
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    // Find the longest palindromic prefix
    let maxLen = 0;
    for (let i = 0; i < n; i++) {
        if (i - d[i] + 1 === 0) {
            maxLen = Math.max(maxLen, d[i] - 1);
        }
    }
    // Return the shortest palindrome by prepending reverse of the non-palindromic suffix
    return s.substring(maxLen).split('').reverse().join('') + s;
};
