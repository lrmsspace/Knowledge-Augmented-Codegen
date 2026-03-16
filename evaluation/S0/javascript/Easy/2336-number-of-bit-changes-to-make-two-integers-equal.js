// Source: https://leetcode.com/problems/number-of-bit-changes-to-make-two-integers-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers n and k.
//
// You can choose any bit in the binary representation of n that is equal to 1 and change it to 0.
//
// Return the number of changes needed to make n equal to k. If it is impossible, return -1.
//
// Example:
// Input: n = 13, k = 4
//
// Output: 2
//
// Explanation:
// Initially, the binary representations of n and k are n = (1101)2 and k = (0100)2.
// We can change the first and fourth bits of n. The resulting integer is n = (0100)2 = k.
//
// Constraints:
// 1 <= n, k <= 106
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var minChanges = function(n, k) {
    if ((n | k) !== n) {
        return -1;
    }
    let changes = 0;
    let diff = n ^ k;
    while (diff > 0) {
        changes += diff & 1;
        diff >>= 1;
    }
    return changes;
};