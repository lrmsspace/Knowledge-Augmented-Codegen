// Source: https://leetcode.com/problems/find-the-longest-semi-repetitive-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given a digit string s that consists of digits from 0 to 9.
//
// A string is called semi-repetitive if there is at most one adjacent pair of the same digit. For example, "0010", "002020", "0123", "2002", and "54944" are semi-repetitive while the following are not: "00101022" (adjacent same digit pairs are 00 and 22), and "1101234883" (adjacent same digit pairs are 11 and 88).
//
// Return the length of the longest semi-repetitive substring of s.
//
// Example:
// Input: s = "52233"
//
// Output: 4
//
// Explanation:
//
// The longest semi-repetitive substring is "5223". Picking the whole string "52233" has two adjacent same digit pairs 22 and 33, but at most one is allowed.
//
// Constraints:
// 1 <= s.length <= 50
// 	'0' <= s[i] <= '9'
//

/**
 * @param {string} s
 * @return {number}
 */
var longestSemiRepetitiveSubstring = function(s) {
    let left = 0;
    let maxLength = 1;
    let sameCount = 0;

    for (let right = 1; right < s.length; right++) {
        if (s[right] === s[right - 1]) {
            sameCount++;
        }

        while (sameCount > 1) {
            if (s[left] === s[left + 1]) {
                sameCount--;
            }
            left++;
        }

        maxLength = Math.max(maxLength, right - left + 1);
    }

    return maxLength;
};