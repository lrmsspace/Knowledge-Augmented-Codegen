// Source: https://leetcode.com/problems/reverse-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of reverse pairs in the array.
//
// A reverse pair is a pair (i, j) where:
//
//
// 	0 <= i < j < nums.length and
// 	nums[i] > 2 * nums[j].
//
// Example:
// Input: nums = [1,3,2,3,1]
// Output: 2
// Explanation: The reverse pairs are:
// (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
// (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-231 <= nums[i] <= 231 - 1
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var reversePairs = function(nums) {
    const mergeSort = (start, end) => {
        if (start >= end) return 0;
        const mid = Math.floor((start + end) / 2);
        let count = mergeSort(start, mid) + mergeSort(mid + 1, end);
        let j = mid + 1;
        for (let i = start; i <= mid; i++) {
            while (j <= end && nums[i] > 2 * nums[j]) {
                j++;
            }
            count += j - (mid + 1);
        }
        const temp = [];
        let left = start, right = mid + 1;
        while (left <= mid && right <= end) {
            if (nums[left] <= nums[right]) {
                temp.push(nums[left++]);
            } else {
                temp.push(nums[right++]);
            }
        }
        while (left <= mid) {
            temp.push(nums[left++]);
        }
        while (right <= end) {
            temp.push(nums[right++]);
        }
        for (let i = start; i <= end; i++) {
            nums[i] = temp[i - start];
        }
        return count;
    }
    return mergeSort(0, nums.length - 1);   
    
};
