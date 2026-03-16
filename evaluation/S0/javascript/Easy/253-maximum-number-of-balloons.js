// Source: https://leetcode.com/problems/maximum-number-of-balloons/   |   Difficulty: Easy
//
// Problem Description:
// Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.
//
// You can use each character in text at most once. Return the maximum number of instances that can be formed.
//
// Example:
// Input: text = "nlaebolko"
// Output: 1
//
// Constraints:
// 1 <= text.length <= 104
// 	text consists of lower case English letters only.
//
//
//  
// Note: This question is the same as  2287: Rearrange Characters to Make Target String.
//

/**
 * @param {string} text
 * @return {number}
 */
var maxNumberOfBalloons = function(text) {
    const charCount = { b: 0, a: 0, l: 0, o: 0, n: 0 };
    for (const char of text) {
        if (charCount.hasOwnProperty(char)) {
            charCount[char]++;
        }
    }
    charCount['l'] = Math.floor(charCount['l'] / 2);
    charCount['o'] = Math.floor(charCount['o'] / 2);

    return Math.min(charCount['b'], charCount['a'], charCount['l'], charCount['o'], charCount['n']);
};
