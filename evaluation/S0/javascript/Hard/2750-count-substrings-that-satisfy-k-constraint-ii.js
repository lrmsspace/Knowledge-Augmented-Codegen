// Source: https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s and an integer k.
//
// You are also given a 2D integer array queries, where queries[i] = [li, ri].
//
// A binary string satisfies the k-constraint if either of the following conditions holds:
//
//
// 	The number of 0's in the string is at most k.
// 	The number of 1's in the string is at most k.
//
//
// Return an integer array answer, where answer[i] is the number of substrings of s[li..ri] that satisfy the k-constraint.
//
// Example:
// Input: s = "0001111", k = 2, queries = [[0,6]]
//
// Output: [26]
//
// Explanation:
//
// For the query [0, 6], all substrings of s[0..6] = "0001111" satisfy the k-constraint except for the substrings s[0..5] = "000111" and s[0..6] = "0001111".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
// 	1 <= k <= s.length
// 	1 <= queries.length <= 105
// 	queries[i] == [li, ri]
// 	0 <= li <= ri < s.length
// 	All queries are distinct.
//

/**
 * @param {string} s
 * @param {number} k
 * @param {number[][]} queries
 * @return {number[]}
 */
var countKConstraintSubstrings = function(s, k, queries) {
    const n = s.length;
    const prefixZeros = Array(n + 1).fill(0);
    const prefixOnes = Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixZeros[i + 1] = prefixZeros[i] + (s[i] === '0' ? 1 : 0);
        prefixOnes[i + 1] = prefixOnes[i] + (s[i] === '1' ? 1 : 0);
    }
    const results = [];
    for (const [l, r] of queries) {
        let count = 0;
        for (let start = l; start <= r; start++) {
            for (let end = start; end <= r; end++) {
                const zeros = prefixZeros[end + 1] - prefixZeros[start];
                const ones = prefixOnes[end + 1] - prefixOnes[start];
                if (zeros <= k || ones <= k) {
                    count++;
                }
            }
        }
        results.push(count);
    }
    return results;
};
