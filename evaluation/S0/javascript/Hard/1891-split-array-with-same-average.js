// Source: https://leetcode.com/problems/split-array-with-same-average/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// You should move each element of nums into one of the two arrays A and B such that A and B are non-empty, and average(A) == average(B).
//
// Return true if it is possible to achieve that and false otherwise.
//
// Note that for an array arr, average(arr) is the sum of all the elements of arr over the length of arr.
//
// Example:
// Input: nums = [1,2,3,4,5,6,7,8]
// Output: true
// Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
//
// Constraints:
// 1 <= nums.length <= 30
// 	0 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var splitArraySameAverage = function(nums) {
    
    const n = nums.length;
    const totalSum = nums.reduce((a, b) => a + b, 0);
    for (let size = 1; size <= Math.floor(n / 2); size++) {
        if ((totalSum * size) % n === 0) {
            const targetSum = (totalSum * size) / n;
            const dp = new Set();
            dp.add(0);
            for (const num of nums) {
                const newDp = new Set(dp);
                for (const sum of dp) {
                    const newSum = sum + num;
                    if (newSum === targetSum) {
                        return true;
                    }
                    newDp.add(newSum);
                }
                dp.clear();
                for (const sum of newDp) {
                    dp.add(sum);
                }
            }
        }
    }
    return false;

    
};
