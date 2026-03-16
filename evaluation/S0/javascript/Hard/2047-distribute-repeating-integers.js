// Source: https://leetcode.com/problems/distribute-repeating-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
//
//
// 	The ith customer gets exactly quantity[i] integers,
// 	The integers the ith customer gets are all equal, and
// 	Every customer is satisfied.
//
//
// Return true if it is possible to distribute nums according to the above conditions.
//
// Example:
// Input: nums = [1,2,3,4], quantity = [2]
// Output: false
// Explanation: The 0th customer cannot be given two different integers.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= 1000
// 	m == quantity.length
// 	1 <= m <= 10
// 	1 <= quantity[i] <= 105
// 	There are at most 50 unique values in nums.
//

/**
 * @param {number[]} nums
 * @param {number[]} quantity
 * @return {boolean}
 */
var canDistribute = function(nums, quantity) {
    const freq = new Map();
    for (const num of nums) {
        freq.set(num, (freq.get(num) || 0) + 1);
    }
    const counts = Array.from(freq.values());
    const m = quantity.length;
    const memo = new Map();

    const canDistributeHelper = (index, mask) => {
        if (index === m) return true;
        const key = `${index}-${mask}`;
        if (memo.has(key)) return memo.get(key);

        for (let i = 0; i < counts.length; i++) {
            if ((mask & (1 << i)) === 0 && counts[i] >= quantity[index]) {
                counts[i] -= quantity[index];
                if (canDistributeHelper(index + 1, mask | (1 << i))) {
                    memo.set(key, true);
                    counts[i] += quantity[index];
                    return true;
                }
                counts[i] += quantity[index];
            }
        }
        memo.set(key, false);
        return false;
    };

    return canDistributeHelper(0, 0);
};
