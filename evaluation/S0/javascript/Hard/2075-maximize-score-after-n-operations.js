// Source: https://leetcode.com/problems/maximize-score-after-n-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
//
// In the ith operation (1-indexed), you will:
//
//
// 	Choose two elements, x and y.
// 	Receive a score of i * gcd(x, y).
// 	Remove x and y from nums.
//
//
// Return the maximum score you can receive after performing n operations.
//
// The function gcd(x, y) is the greatest common divisor of x and y.
//
// Example:
// Input: nums = [1,2]
// Output: 1
// Explanation: The optimal choice of operations is:
// (1 * gcd(1, 2)) = 1
//
// Constraints:
// 1 <= n <= 7
// 	nums.length == 2 * n
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxScore = function(nums) {
    const n = nums.length / 2;
    const gcd = (a, b) => b === 0 ? a : gcd(b, a % b);
    const memo = new Map();
    const backtrack = (mask, op) => {
        if (op > n) return 0;
        if (memo.has(mask)) return memo.get(mask);
        let maxScore = 0;
        for (let i = 0; i < nums.length; i++) {
            if ((mask & (1 << i)) !== 0) continue;

            for (let j = i + 1; j < nums.length; j++) {
                if ((mask & (1 << j)) !== 0) continue;
                const newMask = mask | (1 << i) | (1 << j);
                const score = op * gcd(nums[i], nums[j]) + backtrack(newMask, op + 1);
                maxScore = Math.max(maxScore, score);
            }
        }
        memo.set(mask, maxScore);
        return maxScore;
    }
    return backtrack(0, 1); 
};
