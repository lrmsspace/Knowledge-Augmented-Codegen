// Source: https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array groups of length n. You are also given an integer array nums.
//
// You are asked if you can choose n disjoint subarrays from the array nums such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0, the (i-1)th subarray appears before the ith subarray in nums (i.e. the subarrays must be in the same order as groups).
//
// Return true if you can do this task, and false otherwise.
//
// Note that the subarrays are disjoint if and only if there is no index k such that nums[k] belongs to more than one subarray. A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
// Output: true
// Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
// These subarrays are disjoint as they share no common nums[k] element.
//
// Constraints:
// groups.length == n
// 	1 <= n <= 103
// 	1 <= groups[i].length, sum(groups[i].length) <= 103
// 	1 <= nums.length <= 103
// 	-107 <= groups[i][j], nums[k] <= 107
//

/**
 * @param {number[][]} groups
 * @param {number[]} nums
 * @return {boolean}
 */
var canChoose = function(groups, nums) {
    let index = 0;
    for (const group of groups) {
        let found = false;
        while (index + group.length <= nums.length) {
            let match = true;

            for (let i = 0; i < group.length; i++) {
                if (nums[index + i] !== group[i]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                found = true;
                index += group.length;
                break;
            } else {
                index++;
            }
        }

        if (!found) {
            return false;
        }
    }
    return true;
};
