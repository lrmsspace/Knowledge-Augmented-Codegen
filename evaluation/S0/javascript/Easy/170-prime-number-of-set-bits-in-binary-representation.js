// Source: https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/   |   Difficulty: Easy
//
// Problem Description:
// Given two integers left and right, return the count of numbers in the inclusive range [left, right] having a prime number of set bits in their binary representation.
//
// Recall that the number of set bits an integer has is the number of 1's present when written in binary.
//
//
// 	For example, 21 written in binary is 10101, which has 3 set bits.
//
// Example:
// Input: left = 6, right = 10
// Output: 4
// Explanation:
// 6  -> 110 (2 set bits, 2 is prime)
// 7  -> 111 (3 set bits, 3 is prime)
// 8  -> 1000 (1 set bit, 1 is not prime)
// 9  -> 1001 (2 set bits, 2 is prime)
// 10 -> 1010 (2 set bits, 2 is prime)
// 4 numbers have a prime number of set bits.
//
// Constraints:
// 1 <= left <= right <= 106
// 	0 <= right - left <= 104
//

/**
 * @param {number} left
 * @param {number} right
 * @return {number}
 */
var countPrimeSetBits = function(left, right) {
    const isPrime = (n) => {
        if (n < 2) return false;
        for (let i = 2; i * i <= n; i++) {
            if (n % i === 0) return false;
        }
        return true;
    };

    let count = 0;
    for (let num = left; num <= right; num++) {
        const setBits = num.toString(2).split('0').join('').length;
        if (isPrime(setBits)) {
            count++;
        }
    }
    return count;
};