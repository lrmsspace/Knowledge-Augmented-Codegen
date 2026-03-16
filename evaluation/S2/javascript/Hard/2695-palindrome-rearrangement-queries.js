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
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
//   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
//   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
//   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
//   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
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
    const prefixCounts = Array.from({ length: n + 1 }, () => new Array(26).fill(0));
    
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < 26; j++) {
            prefixCounts[i + 1][j] = prefixCounts[i][j];
        }
        prefixCounts[i + 1][s.charCodeAt(i) - 97]++;
    }
    
    const answers = [];
    
    for (const [a, b, c, d] of queries) {
        const countMap = new Array(26).fill(0);
        
        for (let j = 0; j < 26; j++) {
            countMap[j] += prefixCounts[b + 1][j] - prefixCounts[a][j];
            countMap[j] += prefixCounts[d + 1][j] - prefixCounts[c][j];
        }
        
        let oddCount = 0;
        for (const count of countMap) {
            if (count % 2 !== 0) {
                oddCount++;
            }
        }
        
        answers.push(oddCount <= 1);
    }
    
    return answers;
};
