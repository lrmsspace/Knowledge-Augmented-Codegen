// Source: https://leetcode.com/problems/minimum-incompatibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size such that there are no two equal elements in the same subset.
//
// A subset's incompatibility is the difference between the maximum and minimum elements in that array.
//
// Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.
//
// A subset is a group integers that appear in the array with no particular order.
//
// Example:
// Input: nums = [1,2,1,4], k = 2
// Output: 4
// Explanation: The optimal distribution of subsets is [1,2] and [1,4].
// The incompatibility is (2-1) + (4-1) = 4.
// Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	nums.length is divisible by k
// 	1 <= nums[i] <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minimumIncompatibility = function(nums, k) {
    const n = nums.length;
    const subsetSize = n / k;
    const freq = new Map();
    for (const num of nums) {
        freq.set(num, (freq.get(num) || 0) + 1);
        if (freq.get(num) > k) {
            return -1; 
        }
    }
    const uniqueNums = Array.from(freq.keys()).sort((a, b) => a - b);
    const memo = new Map();

    const backtrack = (index, mask) => {
        if (index === uniqueNums.length) {
            return 0;
        }
        const key = `${index}-${mask}`;
        if (memo.has(key)) {
            return memo.get(key);
        }
        let minIncompatibility = Infinity;
        for (let i = 0; i < k; i++) {
            if ((mask & (1 << i)) === 0) {
                const newMask = mask | (1 << i);
                const incompatibility = backtrack(index + 1, newMask);
                if (incompatibility !== -1) {
                    const currentIncompatibility = uniqueNums[index] - uniqueNums[index - subsetSize];
                    minIncompatibility = Math.min(minIncompatibility, incompatibility + currentIncompatibility);
                }
            }
        }
        const result = minIncompatibility === Infinity ? -1 : minIncompatibility;
        memo.set(key, result);
        return result;
    }
    return backtrack(0, 0);
};
