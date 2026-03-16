// Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
//
// A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
//
// Constraints:
// 1 <= n <= 50
//

/**
 * @param {number} n
 * @return {number}
 */
var countVowelStrings = function(n) {
    // Using combinatorial mathematics: C(n + k - 1, k - 1) where k = 5 (number of vowels)
    const k = 5;
    const N = n + k - 1;
    const K = k - 1;

    // Function to calculate factorial
    const factorial = (num) => {
        let result = 1;
        for (let i = 2; i <= num; i++) {
            result *= i;
        }
        return result;
    };

    // Function to calculate combination C(n, k)
    const combination = (n, k) => {
        return factorial(n) / (factorial(k) * factorial(n - k));
    };

    return combination(N, K);
};