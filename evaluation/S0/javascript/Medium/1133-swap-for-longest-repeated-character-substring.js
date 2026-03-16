// Source: https://leetcode.com/problems/swap-for-longest-repeated-character-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string text. You can swap two of the characters in the text.
//
// Return the length of the longest substring with repeated characters.
//
// Example:
// Input: text = "ababa"
// Output: 3
// Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa" with length 3.
//
// Constraints:
// 1 <= text.length <= 2 * 104
// 	text consist of lowercase English characters only.
//

/**
 * @param {string} text
 * @return {number}
 */
var maxRepOpt1 = function(text) {
    const n = text.length;
    const count = {};
    for (const char of text) {
        count[char] = (count[char] || 0) + 1;
    }
    let maxLen = 0;
    for (let i = 0; i < n; ) {
        let j = i;
        while (j < n && text[j] === text[i]) {
            j++;
        }
        const currentChar = text[i];
        const currentLen = j - i;
        let totalLen = currentLen < count[currentChar] ? currentLen + 1 : currentLen;
        maxLen = Math.max(maxLen, totalLen);
        let k = j + 1;
        while (k < n) {
            let l = k;
            while (l < n && text[l] === text[i]) {
                l++;
            }
            const nextLen = l - k;
            if (nextLen > 0) {
                let combinedLen = currentLen + nextLen;
                if (combinedLen < count[currentChar]) {
                    combinedLen += 1;
                }
                maxLen = Math.max(maxLen, combinedLen);
            }
            k = l + 1;
        }
        i = j;
    }
    return maxLen;  
};
