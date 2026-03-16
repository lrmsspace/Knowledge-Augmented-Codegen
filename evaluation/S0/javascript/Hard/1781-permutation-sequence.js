// Source: https://leetcode.com/problems/permutation-sequence/   |   Difficulty: Hard
//
// Problem Description:
// The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
//
// By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
//
//
// 	"123"
// 	"132"
// 	"213"
// 	"231"
// 	"312"
// 	"321"
//
//
// Given n and k, return the kth permutation sequence.
//
// Example:
// Input: n = 3, k = 3
// Output: "213"
//
// Constraints:
// 1 <= n <= 9
// 	1 <= k <= n!
//

/**
 * @param {number} n
 * @param {number} k
 * @return {string}
 */
var getPermutation = function(n, k) {
    let fact = [1];
    for (let i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    k--; // Convert to 0-based index
    let numbers = [];
    for (let i = 1; i <= n; i++) {
        numbers.push(i);
    }
    let result = '';
    for (let i = n; i >= 1; i--) {
        let idx = Math.floor(k / fact[i - 1]);
        result += numbers[idx];
        numbers.splice(idx, 1);
        k %= fact[i - 1];
    }
    return result;
        
};
