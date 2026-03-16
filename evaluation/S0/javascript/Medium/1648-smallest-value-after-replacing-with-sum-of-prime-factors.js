// Source: https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// Continuously replace n with the sum of its prime factors.
//
//
// 	Note that if a prime factor divides n multiple times, it should be included in the sum as many times as it divides n.
//
//
// Return the smallest value n will take on.
//
// Example:
// Input: n = 15
// Output: 5
// Explanation: Initially, n = 15.
// 15 = 3 * 5, so replace n with 3 + 5 = 8.
// 8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
// 6 = 2 * 3, so replace n with 2 + 3 = 5.
// 5 is the smallest value n will take on.
//
// Constraints:
// 2 <= n <= 105
//

/**
 * @param {number} n
 * @return {number}
 */
var smallestValue = function(n) {
    const getPrimeFactorsSum = (num) => {
        let sum = 0;
        let factor = 2;
        while (factor * factor <= num) {
            while (num % factor === 0) {
                sum += factor;
                num /= factor;
            }
            factor++;
        }
        if (num > 1) {
            sum += num;
        }
        return sum;
    };
    let current = n;
    while (true) {
        const primeFactorsSum = getPrimeFactorsSum(current);
        if (primeFactorsSum === current) {
            break;
        }
        current = primeFactorsSum;
    }
    return current;
};  
