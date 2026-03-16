// Source: https://leetcode.com/problems/substring-with-largest-variance/   |   Difficulty: Hard
//
// Problem Description:
// The variance of a string is defined as the largest difference between the number of occurrences of any 2 characters present in the string. Note the two characters may or may not be the same.
//
// Given a string s consisting of lowercase English letters only, return the largest variance possible among all substrings of s.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aababbb"
// Output: 3
// Explanation:
// All possible variances along with their respective substrings are listed below:
// - Variance 0 for substrings "a", "aa", "ab", "abab", "aababb", "ba", "b", "bb", and "bbb".
// - Variance 1 for substrings "aab", "aba", "abb", "aabab", "ababb", "aababbb", and "bab".
// - Variance 2 for substrings "aaba", "ababbb", "abbb", and "babb".
// - Variance 3 for substring "babbb".
// Since the largest possible variance is 3, we return it.
//
// Constraints:
// 1 <= s.length <= 104
//  s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var largestVariance = function(s) {
    const n = s.length;
    const charCount = new Array(26).fill(0);
    for (let i = 0; i < n; i++) {
        charCount[s.charCodeAt(i) - 'a'.charCodeAt(0)]++;
    }
    let maxVariance = 0;
    for (let i = 0; i < 26; i++) {
        for (let j = 0; j < 26; j++) {
            if (i === j || charCount[i] === 0 || charCount[j] === 0) continue;
            let count1 = 0;
            let count2 = 0;
            for (let k = 0; k < n; k++) {
                const charIndex = s.charCodeAt(k) - 'a'.charCodeAt(0);
                if (charIndex === i) {
                    count1++;
                }
                if (charIndex === j) {
                    count2++;
                }
                if (count1 > 0 && count2 > 0) {
                    maxVariance = Math.max(maxVariance, Math.abs(count1 - count2));
                }
                if (count2 > count1) {
                    count1 = 0;
                    count2 = 0;
                }
            }
        }
    }
    return maxVariance;
};
