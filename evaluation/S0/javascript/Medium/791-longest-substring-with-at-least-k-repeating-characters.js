// Source: https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
//
// if no such substring exists, return 0.
//
// Example:
// Input: s = "aaabb", k = 3
// Output: 3
// Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of only lowercase English letters.
// 	1 <= k <= 105
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var longestSubstring = function(s, k) {
    const helper = (start, end) => {
        if (end - start + 1 < k) return 0;
        const charCount = new Array(26).fill(0);
        for (let i = start; i <= end; i++) {
            charCount[s.charCodeAt(i) - 'a'.charCodeAt(0)]++;
        }
        for (let mid = start; mid <= end; mid++) {
            if (charCount[s.charCodeAt(mid) - 'a'.charCodeAt(0)] < k) {
                let midNext = mid + 1;
                while (midNext <= end && charCount[s.charCodeAt(midNext) - 'a'.charCodeAt(0)] < k) {
                    midNext++;
                }
                return Math.max(helper(start, mid - 1), helper(midNext, end));
            }
        }
        return end - start + 1;
    }
    return helper(0, s.length - 1); 
};
