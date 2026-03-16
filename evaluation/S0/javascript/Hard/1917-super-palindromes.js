// Source: https://leetcode.com/problems/super-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Let's say a positive integer is a super-palindrome if it is a palindrome, and it is also the square of a palindrome.
//
// Given two positive integers left and right represented as strings, return the number of super-palindromes integers in the inclusive range [left, right].
//
// Example:
// Input: left = "4", right = "1000"
// Output: 4
// Explanation: 4, 9, 121, and 484 are superpalindromes.
// Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
//
// Constraints:
// 1 <= left.length, right.length <= 18
// 	left and right consist of only digits.
// 	left and right cannot have leading zeros.
// 	left and right represent integers in the range [1, 1018 - 1].
// 	left is less than or equal to right.
//

/**
 * @param {string} left
 * @param {string} right
 * @return {number}
 */
var superpalindromesInRange = function(left, right) {
    const leftNum = BigInt(left);
    const rightNum = BigInt(right);
    let count = 0;
    for (let i = 1; i < 100000; i++) {
        const s = i.toString();
        const palindrome1 = BigInt(s + s.split('').reverse().join(''));
        const palindrome2 = BigInt(s + s.split('').reverse().slice(1).join(''));
        if (palindrome1 * palindrome1 >= leftNum && palindrome1 * palindrome1 <= rightNum && isPalindrome(palindrome1 * palindrome1)) {
            count++;
        }
        if (palindrome2 * palindrome2 >= leftNum && palindrome2 * palindrome2 <= rightNum && isPalindrome(palindrome2 * palindrome2)) {
            count++;
        }
    }
    return count;   
};
