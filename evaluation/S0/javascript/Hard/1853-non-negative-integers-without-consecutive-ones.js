// Source: https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// Given a positive integer n, return the number of the integers in the range [0, n] whose binary representations do not contain consecutive ones.
//
// Example:
// Input: n = 5
// Output: 5
// Explanation:
// Here are the non-negative integers <= 5 with their corresponding binary representations:
// 0 : 0
// 1 : 1
// 2 : 10
// 3 : 11
// 4 : 100
// 5 : 101
// Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
//
// Constraints:
// 1 <= n <= 109
//

/**
 * @param {number} n
 * @return {number}
 */
var findIntegers = function(n) {
    const fib = [1, 2];
    for (let i = 2; i < 31; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    let count = 0, prevBit = 0;
    for (let i = 30; i >= 0; i--) {
        const currentBit = (n >> i) & 1;
        if (currentBit === 1) {
            count += fib[i];
            if (prevBit === 1) {
                break;
            }
        }
        prevBit = currentBit;
    }
    return count + 1; // Include n itself if it does not contain consecutive ones   
};
