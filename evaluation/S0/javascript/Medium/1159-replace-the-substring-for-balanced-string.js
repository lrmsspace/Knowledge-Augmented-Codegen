// Source: https://leetcode.com/problems/replace-the-substring-for-balanced-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and 'R'.
//
// A string is said to be balanced if each of its characters appears n / 4 times where n is the length of the string.
//
// Return the minimum length of the substring that can be replaced with any other string of the same length to make s balanced. If s is already balanced, return 0.
//
// Example:
// Input: s = "QWER"
// Output: 0
// Explanation: s is already balanced.
//
// Constraints:
// n == s.length
// 	4 <= n <= 105
// 	n is a multiple of 4.
// 	s contains only 'Q', 'W', 'E', and 'R'.
//

/**
 * @param {string} s
 * @return {number}
 */
var balancedString = function(s) {
    const n = s.length;
    const count = { Q: 0, W: 0, E: 0, R: 0 };
    for (const char of s) {
        count[char]++;
    }
    let left = 0;
    let minLength = n;
    for (let right = 0; right < n; right++) {
        count[s[right]]--;
        while (left < n && count['Q'] <= n / 4 && count['W'] <= n / 4 && count['E'] <= n / 4 && count['R'] <= n / 4) {
            minLength = Math.min(minLength, right - left + 1);
            count[s[left]]++;
            left++;
        }
    }
    return minLength;
        
};
