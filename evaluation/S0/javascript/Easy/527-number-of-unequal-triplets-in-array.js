// Source: https://leetcode.com/problems/number-of-unequal-triplets-in-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums. Find the number of triplets (i, j, k) that meet the following conditions:
//
//
// 	0 <= i < j < k < nums.length
// 	nums[i], nums[j], and nums[k] are pairwise distinct.
// 	
// 		In other words, nums[i] != nums[j], nums[i] != nums[k], and nums[j] != nums[k].
// 	
// 	
//
//
// Return the number of triplets that meet the conditions.
//
// Example:
// Input: nums = [4,4,2,4,3]
// Output: 3
// Explanation: The following triplets meet the conditions:
// - (0, 2, 4) because 4 != 2 != 3
// - (1, 2, 4) because 4 != 2 != 3
// - (2, 3, 4) because 2 != 4 != 3
// Since there are 3 triplets, we return 3.
// Note that (2, 0, 4) is not a valid triplet because 2 > 0.
//
// Constraints:
// 3 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var unequalTriplets = function(nums) {
    let count = 0;
    const n = nums.length;      
    for (let i = 0; i < n - 2; i++) {   
        for (let j = i + 1; j < n - 1; j++) {
            for (let k = j + 1; k < n; k++) {
                if (nums[i] !== nums[j] && nums[i] !== nums[k] && nums[j] !== nums[k]) {
                    count++;
                }
            }
        }
    }
    return count;
};
