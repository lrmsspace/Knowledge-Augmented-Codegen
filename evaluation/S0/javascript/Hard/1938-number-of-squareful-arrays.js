// Source: https://leetcode.com/problems/number-of-squareful-arrays/   |   Difficulty: Hard
//
// Problem Description:
// An array is squareful if the sum of every pair of adjacent elements is a perfect square.
//
// Given an integer array nums, return the number of permutations of nums that are squareful.
//
// Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].
//
// Example:
// Input: nums = [1,17,8]
// Output: 2
// Explanation: [1,8,17] and [17,8,1] are the valid permutations.
//
// Constraints:
// 1 <= nums.length <= 12
// 	0 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var numSquarefulPerms = function(nums) {
    const n = nums.length;
    const count = new Map();
    for (const num of nums) {
        count.set(num, (count.get(num) || 0) + 1);
    }
    const uniqueNums = Array.from(count.keys());
    const graph = new Map();
    for (let i = 0; i < uniqueNums.length; i++) {
        for (let j = i; j < uniqueNums.length; j++) {
            const sum = uniqueNums[i] + uniqueNums[j];
            const sqrt = Math.sqrt(sum);
            if (sqrt === Math.floor(sqrt)) {
                if (!graph.has(uniqueNums[i])) {
                    graph.set(uniqueNums[i], []);
                }
                if (!graph.has(uniqueNums[j])) {
                    graph.set(uniqueNums[j], []);
                }
                graph.get(uniqueNums[i]).push(uniqueNums[j]);
                graph.get(uniqueNums[j]).push(uniqueNums[i]);
            }
        }
    }
    let result = 0;
    const backtrack = (num, remaining) => {
        if (remaining === 0) {
            result++;
            return;
        }
        for (const next of graph.get(num) || []) {
            if (count.get(next) > 0) {
                count.set(next, count.get(next) - 1);
                backtrack(next, remaining - 1);
                count.set(next, count.get(next) + 1);
            }
        }
    }
    for (const num of uniqueNums) {
        count.set(num, count.get(num) - 1);
        backtrack(num, n - 1);
        count.set(num, count.get(num) + 1);
    }
    return result;  
};
