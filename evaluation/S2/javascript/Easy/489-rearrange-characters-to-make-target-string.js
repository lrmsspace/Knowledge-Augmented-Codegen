// Source: https://leetcode.com/problems/rearrange-characters-to-make-target-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 0-indexed strings s and target. You can take some letters from s and rearrange them to form new strings.
//
// Return the maximum number of copies of target that can be formed by taking letters from s and rearranging them.
//
// Example:
// Input: s = "ilovecodingonleetcode", target = "code"
// Output: 2
// Explanation:
// For the first copy of "code", take the letters at indices 4, 5, 6, and 7.
// For the second copy of "code", take the letters at indices 17, 18, 19, and 20.
// The strings that are formed are "ecod" and "code" which can both be rearranged into "code".
// We can make at most two copies of "code", so we return 2.
//
// Constraints:
// 1 <= s.length <= 100
// 	1 <= target.length <= 10
// 	s and target consist of lowercase English letters.
//
//
//  
// Note: This question is the same as  1189: Maximum Number of Balloons.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {string} target
 * @return {number}
 */
var rearrangeCharacters = function(s, target) {
    const countS = {};
    const countTarget = {};
    
    // Count the frequency of each character in s
    for (const char of s) {
        countS[char] = (countS[char] || 0) + 1;
    }
    
    // Count the frequency of each character in target
    for (const char of target) {
        countTarget[char] = (countTarget[char] || 0) + 1;
    }
    
    let maxCopies = Infinity;
    
    // Calculate how many copies of target can be made from s
    for (const char in countTarget) {
        if (!countS[char]) {
            return 0; // If s doesn't contain a character from target, we can't form any copies
        }
        maxCopies = Math.min(maxCopies, Math.floor(countS[char] / countTarget[char]));
    }
    
    return maxCopies === Infinity ? 0 : maxCopies;
};
