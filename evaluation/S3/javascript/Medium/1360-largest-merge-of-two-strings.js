// Source: https://leetcode.com/problems/largest-merge-of-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2. You want to construct a string merge in the following way: while either word1 or word2 are non-empty, choose one of the following options:
//
//
// 	If word1 is non-empty, append the first character in word1 to merge and delete it from word1.
//
// 	
// 		For example, if word1 = "abc" and merge = "dv", then after choosing this operation, word1 = "bc" and merge = "dva".
// 	
// 	
// 	If word2 is non-empty, append the first character in word2 to merge and delete it from word2.
// 	
// 		For example, if word2 = "abc" and merge = "", then after choosing this operation, word2 = "bc" and merge = "a".
// 	
// 	
//
//
// Return the lexicographically largest merge you can construct.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b. For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: word1 = "cabaa", word2 = "bcaaa"
// Output: "cbcabaaaaa"
// Explanation: One way to get the lexicographically largest merge is:
// - Take from word1: merge = "c", word1 = "abaa", word2 = "bcaaa"
// - Take from word2: merge = "cb", word1 = "abaa", word2 = "caaa"
// - Take from word2: merge = "cbc", word1 = "abaa", word2 = "aaa"
// - Take from word1: merge = "cbca", word1 = "baa", word2 = "aaa"
// - Take from word1: merge = "cbcab", word1 = "aa", word2 = "aaa"
// - Append the remaining 5 a's from word1 and word2 at the end of merge.
//
// Constraints:
// 1 <= word1.length, word2.length <= 3000
// 	word1 and word2 consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
//   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
//   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
//   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
//   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
//   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} word1
 * @param {string} word2
 * @return {string}
 */
var largestMerge = function(word1, word2) {
    let merge = '';
    let i = 0, j = 0;
    while (i < word1.length && j < word2.length) {
        if (word1.substring(i) > word2.substring(j)) {
            merge += word1[i];
            i++;
        } else {
            merge += word2[j];
            j++;
        }
    }
    merge += word1.substring(i);
    merge += word2.substring(j);
    return merge;
};
