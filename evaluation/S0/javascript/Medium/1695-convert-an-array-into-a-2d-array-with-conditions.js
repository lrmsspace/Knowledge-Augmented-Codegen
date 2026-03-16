// Source: https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You need to create a 2D array from nums satisfying the following conditions:
//
//
// 	The 2D array should contain only the elements of the array nums.
// 	Each row in the 2D array contains distinct integers.
// 	The number of rows in the 2D array should be minimal.
//
//
// Return the resulting array. If there are multiple answers, return any of them.
//
// Note that the 2D array can have a different number of elements on each row.
//
// Example:
// Input: nums = [1,3,4,1,2,3,1]
// Output: [[1,3,4,2],[1,3],[1]]
// Explanation: We can create a 2D array that contains the following rows:
// - 1,3,4,2
// - 1,3
// - 1
// All elements of nums were used, and each row of the 2D array contains distinct integers, so it is a valid answer.
// It can be shown that we cannot have less than 3 rows in a valid array.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= nums.length
//

/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var findMatrix = function(nums) {
    const freqMap = new Map();
    let maxFreq = 0;
    for (const num of nums) {
        const freq = (freqMap.get(num) || 0) + 1;
        freqMap.set(num, freq);
        maxFreq = Math.max(maxFreq, freq);
    }
    const result = Array.from({ length: maxFreq }, () => []);
    for (const [num, freq] of freqMap.entries()) {
        for (let i = 0; i < freq; i++) {
            result[i].push(num);
        }
    }
    return result;
        
};
