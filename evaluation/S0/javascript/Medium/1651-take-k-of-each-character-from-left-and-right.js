// Source: https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k. Each minute, you may take either the leftmost character of s, or the rightmost character of s.
//
// Return the minimum number of minutes needed for you to take at least k of each character, or return -1 if it is not possible to take k of each character.
//
// Example:
// Input: s = "aabaaaacaabc", k = 2
// Output: 8
// Explanation: 
// Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
// Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
// A total of 3 + 5 = 8 minutes is needed.
// It can be proven that 8 is the minimum number of minutes needed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only the letters 'a', 'b', and 'c'.
// 	0 <= k <= s.length
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var takeCharacters = function(s, k) {
    const totalCount = { 'a': 0, 'b': 0, 'c': 0 };
    for (const char of s) {
        totalCount[char]++;
    }
    if (totalCount['a'] < k || totalCount['b'] < k || totalCount['c'] < k) {
        return -1;
    }
    let left = 0;
    let right = s.length - 1;
    const currentCount = { 'a': 0, 'b': 0, 'c': 0 };
    let result = s.length;

    while (right >= 0 && (currentCount['a'] < k || currentCount['b'] < k || currentCount['c'] < k)) {
        currentCount[s[right]]++;
        right--;
    }

    if (currentCount['a'] < k || currentCount['b'] < k || currentCount['c'] < k) {
        return -1;
    }

    result = Math.min(result, s.length - right - 1);

    while (left < s.length && right < s.length) {
        currentCount[s[left]]++;
        left++;

        while (right + 1 < s.length && (currentCount['a'] - (s[right + 1] === 'a' ? 1 : 0) >= k) &&
               (currentCount['b'] - (s[right + 1] === 'b' ? 1 : 0) >= k) &&
               (currentCount['c'] - (s[right + 1] === 'c' ? 1 : 0) >= k)) {
            currentCount[s[right + 1]]--;
            right++;
        }

        if (currentCount['a'] >= k && currentCount['b'] >= k && currentCount['c'] >= k) {
            result = Math.min(result, left + s.length - right - 1);
        }
    }

    return result;
};