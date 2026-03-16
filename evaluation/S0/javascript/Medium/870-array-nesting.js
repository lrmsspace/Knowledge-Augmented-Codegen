// Source: https://leetcode.com/problems/array-nesting/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].
//
// You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:
//
//
// 	The first element in s[k] starts with the selection of the element nums[k] of index = k.
// 	The next element in s[k] should be nums[nums[k]], and then nums[nums[nums[k]]], and so on.
// 	We stop adding right before a duplicate element occurs in s[k].
//
//
// Return the longest length of a set s[k].
//
// Example:
// Input: nums = [5,4,0,3,1,6,2]
// Output: 4
// Explanation: 
// nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
// One of the longest sets s[k]:
// s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < nums.length
// 	All the values of nums are unique.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var arrayNesting = function(nums) {
    const n = nums.length;
    const visited = new Array(n).fill(false);
    let maxSize = 0;

    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            let size = 0;
            let current = i;
            while (!visited[current]) {
                visited[current] = true;
                current = nums[current];
                size++;
            }
            maxSize = Math.max(maxSize, size);
        }
    }

    return maxSize;
};