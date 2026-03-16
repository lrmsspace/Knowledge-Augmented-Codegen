// Source: https://leetcode.com/problems/sort-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums, sort the array in ascending order and return it.
//
// You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
//
// Example:
// Input: nums = [5,2,3,1]
// Output: [1,2,3,5]
// Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-5 * 104 <= nums[i] <= 5 * 104
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var sortArray = function(nums) {
    if (nums.length <= 1) return nums;

    const merge = (left, right) => {
        const result = [];
        let i = 0, j = 0;
        while (i < left.length && j < right.length) {
            if (left[i] < right[j]) {
                result.push(left[i]);
                i++;
            } else {
                result.push(right[j]);
                j++;
            }
        }
        while (i < left.length) {
            result.push(left[i]);
            i++;
        }
        while (j < right.length) {
            result.push(right[j]);
            j++;
        }
        return result;
    };

    const mergeSort = (arr) => {
        if (arr.length <= 1) return arr;
        const mid = Math.floor(arr.length / 2);
        const left = mergeSort(arr.slice(0, mid));
        const right = mergeSort(arr.slice(mid));
        return merge(left, right);
    };

    return mergeSort(nums);
};  