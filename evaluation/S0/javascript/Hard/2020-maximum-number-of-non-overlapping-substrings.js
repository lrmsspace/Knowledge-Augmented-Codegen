// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

/**
 * @param {string} s
 * @return {string[]}
 */
var maxNumOfSubstrings = function(s) {
    const n = s.length;
    const charRange = new Array(26).fill(0).map(() => [n, -1]);
    for (let i = 0; i < n; i++) {
        const charIndex = s.charCodeAt(i) - 'a'.charCodeAt(0);
        charRange[charIndex][0] = Math.min(charRange[charIndex][0], i);
        charRange[charIndex][1] = Math.max(charRange[charIndex][1], i);
    }
    const intervals = [];
    for (let i = 0; i < 26; i++) {
        if (charRange[i][1] !== -1) {
            intervals.push(charRange[i]);
        }
    }
    intervals.sort((a, b) => a[1] - b[1]);
    const result = [];
    let lastEnd = -1;
    for (const [start, end] of intervals) {
        if (start > lastEnd) {
            result.push(s.substring(start, end + 1));
            lastEnd = end;
        }
    }
    return result;  
};
