// Source: https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s of length n on which you can apply two types of operations:
//
//
// 	Choose an index i and invert all characters from index 0 to index i (both inclusive), with a cost of i + 1
// 	Choose an index i and invert all characters from index i to index n - 1 (both inclusive), with a cost of n - i
//
//
// Return the minimum cost to make all characters of the string equal.
//
// Invert a character means if its value is '0' it becomes '1' and vice-versa.
//
// Example:
// Input: s = "0011"
// Output: 2
// Explanation: Apply the second operation with i = 2 to obtain s = "0000" for a cost of 2. It can be shown that 2 is the minimum cost to make all characters equal.
//
// Constraints:
// 1 <= s.length == n <= 105
// 	s[i] is either '0' or '1'
//

/**
 * @param {string} s
 * @return {number}
 */
var minimumCost = function(s) {
    const n = s.length;
    let costToMakeAllZero = 0;
    let costToMakeAllOne = 0;
    for (let i = 0; i < n - 1; i++) {
        if (s[i] !== s[i + 1]) {
            if (s[i + 1] === '0') {
                costToMakeAllZero += n - (i + 1);
            }
            else {
                costToMakeAllOne += n - (i + 1);
            }
        }
    }
    if (s[0] === '1') {
        costToMakeAllZero += n;
    }
    else {
        costToMakeAllOne += n;
    }
    return Math.min(costToMakeAllZero, costToMakeAllOne);
};
