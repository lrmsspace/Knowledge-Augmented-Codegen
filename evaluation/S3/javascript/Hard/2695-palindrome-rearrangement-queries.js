// Source: https://leetcode.com/problems/palindrome-rearrangement-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s having an even length n.
//
// You are also given a 0-indexed 2D integer array, queries, where queries[i] = [ai, bi, ci, di].
//
// For each query i, you are allowed to perform the following operations:
//
//
// 	Rearrange the characters within the substring s[ai:bi], where 0 <= ai <= bi < n / 2.
// 	Rearrange the characters within the substring s[ci:di], where n / 2 <= ci <= di < n.
//
//
// For each query, your task is to determine whether it is possible to make s a palindrome by performing the operations.
//
// Each query is answered independently of the others.
//
// Return a 0-indexed array answer, where answer[i] == true if it is possible to make s a palindrome by performing operations specified by the ith query, and false otherwise.
//
//
// 	A substring is a contiguous sequence of characters within a string.
// 	s[x:y] represents the substring consisting of characters from the index x to index y in s, both inclusive.
//
// Example:
// Input: s = "abcabc", queries = [[1,1,3,5],[0,2,5,5]]
// Output: [true,true]
// Explanation: In this example, there are two queries:
// In the first query:
// - a0 = 1, b0 = 1, c0 = 3, d0 = 5.
// - So, you are allowed to rearrange s[1:1] => abcabc and s[3:5] => abcabc.
// - To make s a palindrome, s[3:5] can be rearranged to become => abccba.
// - Now, s is a palindrome. So, answer[0] = true.
// In the second query:
// - a1 = 0, b1 = 2, c1 = 5, d1 = 5.
// - So, you are allowed to rearrange s[0:2] => abcabc and s[5:5] => abcabc.
// - To make s a palindrome, s[0:2] can be rearranged to become => cbaabc.
// - Now, s is a palindrome. So, answer[1] = true.
//
// Constraints:
// 2 <= n == s.length <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 4
// 	ai == queries[i][0], bi == queries[i][1]
// 	ci == queries[i][2], di == queries[i][3]
// 	0 <= ai <= bi < n / 2
// 	n / 2 <= ci <= di < n 
// 	n is even.
// 	s consists of only lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var canMakePalindromeQueries = function(s, queries) {
    const n = s.length;
    const prefixCount = Array.from({ length: n + 1 }, () => new Array(26).fill(0));
    
    // Precompute prefix character counts
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < 26; j++) {
            prefixCount[i + 1][j] = prefixCount[i][j];
        }
        prefixCount[i + 1][s.charCodeAt(i) - 'a'.charCodeAt(0)]++;
    }

    const result = [];
    for (const query of queries) {
        const [a, b, c, d] = query;
        const leftHalf = s.substring(a, b + 1);
        const rightHalf = s.substring(c, d + 1);

        // Check if the two halves are of equal length
        if (leftHalf.length !== rightHalf.length) {
            result.push(false);
            continue;
        }

        // Count characters in both halves
        const leftCount = new Array(26).fill(0);
        const rightCount = new Array(26).fill(0);

        for (const ch of leftHalf) {
            leftCount[ch.charCodeAt(0) - 'a'.charCodeAt(0)]++;
        }
        
        for (const ch of rightHalf) {
            rightCount[ch.charCodeAt(0) - 'a'.charCodeAt(0)]++;
        }

        // Check if character counts match
        let isPossible = true;
        for (let i = 0; i < 26; i++) {
            if (leftCount[i] !== rightCount[i]) {
                isPossible = false;
                break;
            }
        }

        result.push(isPossible);
    }

    return result;
};
