// Source: https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, you can do the following operation any number of times:
//
//
// 	Add or subtract a power of 2 from n.
//
//
// Return the minimum number of operations to make n equal to 0.
//
// A number x is power of 2 if x == 2i where i >= 0.
//
// Example:
// Input: n = 39
// Output: 3
// Explanation: We can do the following operations:
// - Add 20 = 1 to n, so now n = 40.
// - Subtract 23 = 8 from n, so now n = 32.
// - Subtract 25 = 32 from n, so now n = 0.
// It can be shown that 3 is the minimum number of operations we need to make n equal to 0.
//
// Constraints:
// 1 <= n <= 105
//

/**
 * @param {number} n
 * @return {number}
 */
var minOperations = function(n) {
    let operations = 0;
    while (n > 0) {
        const lsb = n & -n; // Get the least significant bit (LSB)
        n -= lsb; // Subtract the LSB from n
        operations++;
    }
    return operations;
        
};
