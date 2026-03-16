// Source: https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// Return the largest integer having n digits (as a string) that is k-palindromic.
//
// Note that the integer must not have leading zeros.
//
// Example:
// Input: n = 3, k = 5
//
// Output: "595"
//
// Explanation:
//
// 595 is the largest k-palindromic integer with 3 digits.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= k <= 9
//

/**
 * @param {number} n
 * @param {number} k
 * @return {string}
 */
var largestPalindrome = function(n, k) {
    if (n === 1) {
        for (let i = 9; i >= 0; i--) {
            if (i % k === 0) return i.toString();
        }
        return "-1";
    }
    const halfLength = Math.floor((n + 1) / 2);
    let halfPalindrome = '9'.repeat(halfLength);
    const isEven = n % 2 === 0;
    while (true) {
        let palindromeStr = halfPalindrome;
        if (!isEven) {
            palindromeStr += halfPalindrome.slice(0, -1).split('').reverse().join('');
        }
        else {
            palindromeStr += halfPalindrome.split('').reverse().join('');
        }
        const palindromeNum = BigInt(palindromeStr);
        if (palindromeNum % BigInt(k) === BigInt(0)) {
            return palindromeStr;
        }
        halfPalindrome = (BigInt(halfPalindrome) - BigInt(1)).toString();
        if (halfPalindrome.length < halfLength) {
            return "-1";
        }
    }   
    return "-1";
};
