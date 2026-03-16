// Source: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.
//
// Return true if it is possible. Otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,3,4,4,5,6], k = 4
// Output: true
// Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {boolean}
 */
var isPossibleDivide = function(nums, k) {
    if (nums.length % k !== 0) return false;
    const countMap = new Map();
    for (const num of nums) {
        countMap.set(num, (countMap.get(num) || 0) + 1);
    }
    const uniqueNums = Array.from(countMap.keys()).sort((a, b) => a - b);
    for (const num of uniqueNums) {
        const count = countMap.get(num);
        if (count > 0) {
            for (let i = 0; i < k; i++) {
                const nextNum = num + i;
                if (!countMap.has(nextNum) || countMap.get(nextNum) < count) {
                    return false;
                }
                countMap.set(nextNum, countMap.get(nextNum) - count);
            }
        }
    }
    return true;    
                        
};
