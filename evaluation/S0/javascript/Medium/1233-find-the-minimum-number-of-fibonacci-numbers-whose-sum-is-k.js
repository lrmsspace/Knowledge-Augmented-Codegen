// Source: https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k. The same Fibonacci number can be used multiple times.
//
// The Fibonacci numbers are defined as:
//
//
// 	F1 = 1
// 	F2 = 1
// 	Fn = Fn-1 + Fn-2 for n > 2.
//
// It is guaranteed that for the given constraints we can always find such Fibonacci numbers that sum up to k.
//
// Example:
// Input: k = 7
// Output: 2 
// Explanation: The Fibonacci numbers are: 1, 1, 2, 3, 5, 8, 13, ... 
// For k = 7 we can use 2 + 5 = 7.
//
// Constraints:
// 1 <= k <= 109
//

/**
 * @param {number} k
 * @return {number}
 */
var findMinFibonacciNumbers = function(k) {
    // Generate Fibonacci numbers up to k
    const fibs = [1, 1];
    while (true) {
        const nextFib = fibs[fibs.length - 1] + fibs[fibs.length - 2];
        if (nextFib > k) break;
        fibs.push(nextFib);
    }
    let count = 0;
    // Greedily subtract the largest Fibonacci number less than or equal to k
    for (let i = fibs.length - 1; i >= 0 && k > 0; i--) {
        if (fibs[i] <= k) {
            k -= fibs[i];
            count++;
        }
    }
    return count;
        
};
