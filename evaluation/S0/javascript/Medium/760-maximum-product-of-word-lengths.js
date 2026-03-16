// Source: https://leetcode.com/problems/maximum-product-of-word-lengths/   |   Difficulty: Medium
//
// Problem Description:
// Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. If no such two words exist, return 0.
//
// Example:
// Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
// Output: 16
// Explanation: The two words can be "abcw", "xtfn".
//
// Constraints:
// 2 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	words[i] consists only of lowercase English letters.
//

/**
 * @param {string[]} words
 * @return {number}
 */
var maxProduct = function(words) {
    const n = words.length;
    const bitMasks = new Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        let bitMask = 0;
        for (const char of words[i]) {
            bitMask |= 1 << (char.charCodeAt(0) - 97);
        }
        bitMasks[i] = bitMask;
    }

    let maxProduct = 0;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if ((bitMasks[i] & bitMasks[j]) === 0) {
                maxProduct = Math.max(maxProduct, words[i].length * words[j].length);
            }
        }
    }
    return maxProduct;
};