// Source: https://leetcode.com/problems/number-of-1-bits/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
//
// Example:
// Input: n = 11
//
// Output: 3
//
// Explanation:
//
// The input binary string 1011 has a total of three set bits.
//
// Constraints:
// 1 <= n <= 231 - 1
//
//
//  
// Follow up: If this function is called many times, how would you optimize it?
//

/**
 * @param {number} n
 * @return {number}
 */
var hammingWeight = function(n) {
    let count = 0;
    while (n !== 0) {
        count += n & 1; // Increment count if the least significant bit is 1
        n >>>= 1; // Unsigned right shift n to process the next bit
    }
    return count;
};
