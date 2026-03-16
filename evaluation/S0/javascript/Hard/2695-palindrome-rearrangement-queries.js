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

/**
 * @param {string} s
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var canMakePalindromeQueries = function(s, queries) {
    const n = s.length;
    const prefixCount = Array.from({ length: n + 1 }, () => Array(26).fill(0));
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < 26; j++) {
            prefixCount[i + 1][j] = prefixCount[i][j];
        }
        prefixCount[i + 1][s.charCodeAt(i) - 97]++;
    }

    const result = [];
    for (const [a, b, c, d] of queries) {
        const leftCount = Array(26).fill(0);
        const rightCount = Array(26).fill(0);

        for (let i = 0; i < 26; i++) {
            leftCount[i] = prefixCount[b + 1][i] - prefixCount[a][i];
            rightCount[i] = prefixCount[d + 1][i] - prefixCount[c][i];
        }

        let oddCount = 0;
        for (let i = 0; i < 26; i++) {
            if ((leftCount[i] + rightCount[i]) % 2 !== 0) {
                oddCount++;
            }
        }

        result.push(oddCount <= 1);
    }

    return result;
};