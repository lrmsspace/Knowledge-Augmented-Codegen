// Source: https://leetcode.com/problems/hash-divided-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of length n and an integer k, where n is a multiple of k. Your task is to hash the string s into a new string called result, which has a length of n / k.
//
// First, divide s into n / k substrings, each with a length of k. Then, initialize result as an empty string.
//
// For each substring in order from the beginning:
//
//
// 	The hash value of a character is the index of that character in the English alphabet (e.g., 'a' → 0, 'b' → 1, ..., 'z' → 25).
// 	Calculate the sum of all the hash values of the characters in the substring.
// 	Find the remainder of this sum when divided by 26, which is called hashedChar.
// 	Identify the character in the English lowercase alphabet that corresponds to hashedChar.
// 	Append that character to the end of result.
//
//
// Return result.
//
// Example:
// Input: s = "abcd", k = 2
//
// Output: "bf"
//
// Explanation:
//
// First substring: "ab", 0 + 1 = 1, 1 % 26 = 1, result[0] = 'b'.
//
// Second substring: "cd", 2 + 3 = 5, 5 % 26 = 5, result[1] = 'f'.
//
// Constraints:
// 1 <= k <= 100
// 	k <= s.length <= 1000
// 	s.length is divisible by k.
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var stringHash = function(s, k) {
    let result = '';
    for (let i = 0; i < s.length; i += k) {
        let sum = 0;
        for (let j = i; j < i + k; j++) {
            sum += s.charCodeAt(j) - 'a'.charCodeAt(0);
        }
        const hashedChar = sum % 26;
        result += String.fromCharCode(hashedChar + 'a'.charCodeAt(0));
    }
    return result;
};
