// Source: https://leetcode.com/problems/beautiful-array/   |   Difficulty: Medium
//
// Problem Description:
// An array nums of length n is beautiful if:
//
//
// 	nums is a permutation of the integers in the range [1, n].
// 	For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k] == nums[i] + nums[j].
//
//
// Given the integer n, return any beautiful array nums of length n. There will be at least one valid answer for the given n.
//
// Example:
// Input: n = 4
// Output: [2,1,4,3]
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * @param {number} n
 * @return {number[]}
 */
var beautifulArray = function(n) {
    const build = (start, step, n) => {
        if (start > n) return [];
        const left = build(start, step * 2, n);
        const right = build(start + step, step * 2, n);
        return [...left, start, ...right];
            
    };
        return build(1, 1, n);    
};
