// Source: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting only of characters a, b and c.
//
// Return the number of substrings containing at least one occurrence of all these characters a, b and c.
//
// Example:
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).
//
// Constraints:
// 3 <= s.length <= 5 x 10^4
// 	s only consists of a, b or c characters.
//

/**
 * @param {string} s
 * @return {number}
 */
var numberOfSubstrings = function(s) {
    let count = { 'a': 0, 'b': 0, 'c': 0 };
    let left = 0;
    let result = 0;
    for (let right = 0; right < s.length; right++) {
        count[s[right]]++;
        while (count['a'] > 0 && count['b'] > 0 && count['c'] > 0) {
            count[s[left]]--;
            left++;
        }
        result += left;
    }
    return result;
        
};
