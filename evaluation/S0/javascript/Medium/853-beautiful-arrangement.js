// Source: https://leetcode.com/problems/beautiful-arrangement/   |   Difficulty: Medium
//
// Problem Description:
// Suppose you have n integers labeled 1 through n. A permutation of those n integers perm (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n), either of the following is true:
//
//
// 	perm[i] is divisible by i.
// 	i is divisible by perm[i].
//
//
// Given an integer n, return the number of the beautiful arrangements that you can construct.
//
// Example:
// Input: n = 2
// Output: 2
// Explanation: 
// The first beautiful arrangement is [1,2]:
//     - perm[1] = 1 is divisible by i = 1
//     - perm[2] = 2 is divisible by i = 2
// The second beautiful arrangement is [2,1]:
//     - perm[1] = 2 is divisible by i = 1
//     - i = 2 is divisible by perm[2] = 1
//
// Constraints:
// 1 <= n <= 15
//

/**
 * @param {number} n
 * @return {number}
 */
var countArrangement = function(n) {
    let count = 0;

    const backtrack = (position, used) => {
        if (position > n) {
            count++;
            return;
        }
        for (let i = 1; i <= n; i++) {
            if (!used.has(i) && (i % position === 0 || position % i === 0)) {
                used.add(i);
                backtrack(position + 1, used);
                used.delete(i);
            }
        }
    };

    backtrack(1, new Set());
    return count;
};