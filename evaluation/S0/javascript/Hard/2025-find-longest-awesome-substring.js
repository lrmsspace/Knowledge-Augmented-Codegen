// Source: https://leetcode.com/problems/find-longest-awesome-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it a palindrome.
//
// Return the length of the maximum length awesome substring of s.
//
// Example:
// Input: s = "3242415"
// Output: 5
// Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of digits.
//

/**
 * @param {string} s
 * @return {number}
 */
var longestAwesome = function(s) {
    const n = s.length;
    const prefixMasks = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixMasks[i + 1] = prefixMasks[i] ^ (1 << (s.charCodeAt(i) - '0'.charCodeAt(0)));
    }
    const maskIndexMap = new Map();
    let maxLength = 1;
    for (let i = 0; i <= n; i++) {
        const mask = prefixMasks[i];
        if (maskIndexMap.has(mask)) {
            maxLength = Math.max(maxLength, i - maskIndexMap.get(mask));
        }
        for (let j = 0; j < 10; j++) {
            const toggledMask = mask ^ (1 << j);
            if (maskIndexMap.has(toggledMask)) {
                maxLength = Math.max(maxLength, i - maskIndexMap.get(toggledMask));
            }
        }
        if (!maskIndexMap.has(mask)) {
            maskIndexMap.set(mask, i);
        }
    }
    return maxLength;
};
