// Source: https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string target.
//
// Alice is going to type target on her computer using a special keyboard that has only two keys:
//
//
// 	Key 1 appends the character "a" to the string on the screen.
// 	Key 2 changes the last character of the string on the screen to its next character in the English alphabet. For example, "c" changes to "d" and "z" changes to "a".
//
//
// Note that initially there is an empty string "" on the screen, so she can only press key 1.
//
// Return a list of all strings that appear on the screen as Alice types target, in the order they appear, using the minimum key presses.
//
// Example:
// Input: target = "abc"
//
// Output: ["a","aa","ab","aba","abb","abc"]
//
// Explanation:
//
// The sequence of key presses done by Alice are:
//
//
// 	Press key 1, and the string on the screen becomes "a".
// 	Press key 1, and the string on the screen becomes "aa".
// 	Press key 2, and the string on the screen becomes "ab".
// 	Press key 1, and the string on the screen becomes "aba".
// 	Press key 2, and the string on the screen becomes "abb".
// 	Press key 2, and the string on the screen becomes "abc".
//
// Constraints:
// 1 <= target.length <= 400
// 	target consists only of lowercase English letters.
//

/**
 * @param {string} target
 * @return {string[]}
 */
var stringSequence = function(target) {
    const result = [];
    let currentString = '';
    for (let i = 0; i < target.length; i++) {
        if (i === 0 || target[i] === target[i - 1]) {
            currentString += 'a';
        } else {
            const lastChar = currentString[currentString.length - 1];
            const nextChar = lastChar === 'z' ? 'a' : String.fromCharCode(lastChar.charCodeAt(0) + 1);
            currentString = currentString.slice(0, -1) + nextChar;
        }
        result.push(currentString);
    }
    return result;
};