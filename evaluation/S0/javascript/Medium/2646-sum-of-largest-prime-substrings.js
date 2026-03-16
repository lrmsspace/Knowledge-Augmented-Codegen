// Source: https://leetcode.com/problems/sum-of-largest-prime-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the sum of the 3 largest unique prime numbers that can be formed using any of its substrings.
//
// Return the sum of the three largest unique prime numbers that can be formed. If fewer than three exist, return the sum of all available primes. If no prime numbers can be formed, return 0.
//
// Note: Each prime number should be counted only once, even if it appears in multiple substrings. Additionally, when converting a substring to an integer, any leading zeros are ignored.
//
// Example:
// Input: s = "12234"
//
// Output: 1469
//
// Explanation:
//
//
// 	The unique prime numbers formed from the substrings of "12234" are 2, 3, 23, 223, and 1223.
// 	The 3 largest primes are 1223, 223, and 23. Their sum is 1469.
//
// Constraints:
// 1 <= s.length <= 10
// 	s consists of only digits.
//

/**
 * @param {string} s
 * @return {number}
 */
var sumOfLargestPrimes = function(s) {
    const primes = new Set();
    const n = s.length;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j <= n; j++) {
            const numStr = s.slice(i, j);
            const num = parseInt(numStr, 10);
            if (isPrime(num)) {
                primes.add(num);
            }
        }
    }
    const largestPrimes = Array.from(primes).sort((a, b) => b - a).slice(0, 3);
    return largestPrimes.reduce((sum, prime) => sum + prime, 0);
};
