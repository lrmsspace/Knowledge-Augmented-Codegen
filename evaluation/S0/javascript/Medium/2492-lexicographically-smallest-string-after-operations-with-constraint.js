// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k.
//
// Define a function distance(s1, s2) between two strings s1 and s2 of the same length n as:
//
//
// 	The sum of the minimum distance between s1[i] and s2[i] when the characters from 'a' to 'z' are placed in a cyclic order, for all i in the range [0, n - 1].
//
//
// For example, distance("ab", "cd") == 4, and distance("a", "z") == 1.
//
// You can change any letter of s to any other lowercase English letter, any number of times.
//
// Return a string denoting the lexicographically smallest string t you can get after some changes, such that distance(s, t) <= k.
//
// Example:
// Input: s = "zbbz", k = 3
//
// Output: "aaaz"
//
// Explanation:
//
// Change s to "aaaz". The distance between "zbbz" and "aaaz" is equal to k = 3.
//
// Constraints:
// 1 <= s.length <= 100
// 	0 <= k <= 2000
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var getSmallestString = function(s, k) {
    const n = s.length;
    const result = s.split('');
    for (let i = 0; i < n; i++) {
        const currentCharCode = s.charCodeAt(i) - 97;
        const distanceToA = currentCharCode;
        const distanceToZ = 26 - currentCharCode;
        if (distanceToA <= distanceToZ && distanceToA <= k) {
            result[i] = 'a';
            k -= distanceToA;
        } else if (distanceToZ <= distanceToA && distanceToZ <= k) {
            result[i] = 'z';
            k -= distanceToZ;
        }
    }
    return result.join('');
};
