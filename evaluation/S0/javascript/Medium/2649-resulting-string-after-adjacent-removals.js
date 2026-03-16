// Source: https://leetcode.com/problems/resulting-string-after-adjacent-removals/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of lowercase English letters.
//
// You must repeatedly perform the following operation while the string s has at least two consecutive characters:
//
//
// 	Remove the leftmost pair of adjacent characters in the string that are consecutive in the alphabet, in either order (e.g., 'a' and 'b', or 'b' and 'a').
// 	Shift the remaining characters to the left to fill the gap.
//
//
// Return the resulting string after no more operations can be performed.
//
// Note: Consider the alphabet as circular, thus 'a' and 'z' are consecutive.
//
// Example:
// Input: s = "abc"
//
// Output: "c"
//
// Explanation:
//
//
// 	Remove "ab" from the string, leaving "c" as the remaining string.
// 	No further operations are possible. Thus, the resulting string after all possible removals is "c".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var resultingString = function(s) {
    const stack = [];
    for (const char of s) {
        if (stack.length > 0) {
            const top = stack[stack.length - 1];
            if ((char.charCodeAt(0) - top.charCodeAt(0) + 26) % 26 === 1 || (top.charCodeAt(0) - char.charCodeAt(0) + 26) % 26 === 1) {
                stack.pop();
                continue;
            }
        }
        stack.push(char);
    }
    return stack.join('');
};
