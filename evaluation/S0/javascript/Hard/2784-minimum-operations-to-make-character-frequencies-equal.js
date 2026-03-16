// Source: https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s.
//
// A string t is called good if all characters of t occur the same number of times.
//
// You can perform the following operations any number of times:
//
//
//  Delete a character from s.
//  Insert a character in s.
//  Change a character in s to its next letter in the alphabet.
//
//
// Note that you cannot change 'z' to 'a' using the third operation.
//
// Return the minimum number of operations required to make s good.
//
// Example:
// Input: s = "acab"
//
// Output: 1
//
// Explanation:
//
// We can make s good by deleting one occurrence of character 'a'.
//
// Constraints:
// 3 <= s.length <= 2 * 104
//  s contains only lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var makeStringGood = function(s) {
    const freq = Array(26).fill(0);
    for (const char of s) {
        freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    const nonZeroFreq = freq.filter(f => f > 0);
    const uniqueFreq = Array.from(new Set(nonZeroFreq)).sort((a, b) => a - b);
    let minOperations = Infinity;
    for (const targetFreq of uniqueFreq) {
        let operations = 0;
        for (const f of nonZeroFreq) {
            if (f < targetFreq) {
                operations += targetFreq - f;
            } else if (f > targetFreq) {
                operations += f - targetFreq;
            }




        }        minOperations = Math.min(minOperations, operations);
    }
    return minOperations;
};
