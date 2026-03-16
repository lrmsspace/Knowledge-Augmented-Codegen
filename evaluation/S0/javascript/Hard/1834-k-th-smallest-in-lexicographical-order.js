// Source: https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers n and k, return the kth lexicographically smallest integer in the range [1, n].
//
// Example:
// Input: n = 13, k = 2
// Output: 10
// Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
//
// Constraints:
// 1 <= k <= n <= 109
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var findKthNumber = function(n, k) {
    const countPrefix = (prefix) => {
        let count = 0;
        let current = prefix, next = prefix + 1;
        while (current <= n) {
            count += Math.min(n + 1, next) - current;
            current *= 10;
            next *= 10;
        }
        return count;
    }
    let prefix = 1;
    k--;
    while (k > 0) {
        const count = countPrefix(prefix);
        if (count <= k) {
            prefix++;
            k -= count;
        }
        else {
            prefix *= 10;
            k--;
        }
    }
    return prefix;  
};
