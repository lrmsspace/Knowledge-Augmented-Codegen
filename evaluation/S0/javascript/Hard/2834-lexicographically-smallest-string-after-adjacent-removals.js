// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-adjacent-removals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of lowercase English letters.
//
// You can perform the following operation any number of times (including zero):
//
//
// 	Remove any pair of adjacent characters in the string that are consecutive in the alphabet, in either order (e.g., 'a' and 'b', or 'b' and 'a').
// 	Shift the remaining characters to the left to fill the gap.
//
//
// Return the lexicographically smallest string that can be obtained after performing the operations optimally.
//
// Note: Consider the alphabet as circular, thus 'a' and 'z' are consecutive.
//
// Example:
// Input: s = "abc"
//
// Output: "a"
//
// Explanation:
//
//
// 	Remove "bc" from the string, leaving "a" as the remaining string.
// 	No further operations are possible. Thus, the lexicographically smallest string after all possible removals is "a".
//
// Constraints:
// 1 <= s.length <= 250
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var lexicographicallySmallestString = function(s) {
    const stack = [];
    const isConsecutive = (a, b) => {
        return Math.abs(a.charCodeAt(0) - b.charCodeAt(0)) === 1 || 
               (a === 'a' && b === 'z') || 
               (a === 'z' && b === 'a');
    };
    for (const char of s) {
        if (stack.length > 0 && isConsecutive(stack[stack.length - 1], char)) {
            stack.pop();
        } else {
            stack.push(char);
        }
    }
    return stack.join('');
};
