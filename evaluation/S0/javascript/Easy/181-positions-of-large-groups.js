// Source: https://leetcode.com/problems/positions-of-large-groups/   |   Difficulty: Easy
//
// Problem Description:
// In a string s of lowercase letters, these letters form consecutive groups of the same character.
//
// For example, a string like s = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z", and "yy".
//
// A group is identified by an interval [start, end], where start and end denote the start and end indices (inclusive) of the group. In the above example, "xxxx" has the interval [3,6].
//
// A group is considered large if it has 3 or more characters.
//
// Return the intervals of every large group sorted in increasing order by start index.
//
// Example:
// Input: s = "abbxxxxzzy"
// Output: [[3,6]]
// Explanation: "xxxx" is the only large group with start index 3 and end index 6.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s contains lowercase English letters only.
//

/**
 * @param {string} s
 * @return {number[][]}
 */
var largeGroupPositions = function(s) {
    const result = [];
    let start = 0;
    for (let i = 1; i <= s.length; i++) {
        if (i === s.length || s[i] !== s[i - 1]) {
            if (i - start >= 3) {
                result.push([start, i - 1]);
            }
            start = i;
        }
    }
    return result;
};
