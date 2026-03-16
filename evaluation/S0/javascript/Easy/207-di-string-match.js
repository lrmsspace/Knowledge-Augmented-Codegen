// Source: https://leetcode.com/problems/di-string-match/   |   Difficulty: Easy
//
// Problem Description:
// A permutation perm of n + 1 integers of all the integers in the range [0, n] can be represented as a string s of length n where:
//
//
// 	s[i] == 'I' if perm[i] < perm[i + 1], and
// 	s[i] == 'D' if perm[i] > perm[i + 1].
//
//
// Given a string s, reconstruct the permutation perm and return it. If there are multiple valid permutations perm, return any of them.
//
// Example:
// Input: s = "IDID"
// Output: [0,4,1,3,2]
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either 'I' or 'D'.
//

/**
 * @param {string} s
 * @return {number[]}
 */
var diStringMatch = function(s) {
    const n = s.length;
    let low = 0;
    let high = n;
    const result = [];
    for (let i = 0; i < n; i++) {
        if (s[i] === 'I') {
            result.push(low++);
        } else {
            result.push(high--);
        }
    }
    result.push(low); // or high, both are same here
    return result;
};