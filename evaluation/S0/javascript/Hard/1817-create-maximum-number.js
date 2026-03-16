// Source: https://leetcode.com/problems/create-maximum-number/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.
//
// Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.
//
// Return an array of the k digits representing the answer.
//
// Example:
// Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
// Output: [9,8,6,5,3]
//
// Constraints:
// m == nums1.length
// 	n == nums2.length
// 	1 <= m, n <= 500
// 	0 <= nums1[i], nums2[i] <= 9
// 	1 <= k <= m + n
// 	nums1 and nums2 do not have leading zeros.
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} k
 * @return {number[]}
 */
var maxNumber = function(nums1, nums2, k) {
    const maxNumberFromSingleArray = (nums, k) => {
        const stack = [];
        const toRemove = nums.length - k;
        let removed = 0;
        for (let num of nums) {
            while (stack.length > 0 && stack[stack.length - 1] < num && removed < toRemove) {
                stack.pop();
                removed++;
            }
            stack.push(num);
        }
        return stack.slice(0, k);
    }

    const merge = (arr1, arr2) => { 
        const merged = [];
        let i = 0, j = 0;
        while (i < arr1.length || j < arr2.length) {
            if (i < arr1.length && (j >= arr2.length || arr1.slice(i).join('') > arr2.slice(j).join(''))) {
                merged.push(arr1[i]);
                i++;
            } else {
                merged.push(arr2[j]);
                j++;
            }
        }
        return merged;
    }

    let maxNumber = [];
    for (let i = Math.max(0, k - nums2.length); i <= Math.min(k, nums1.length); i++) {                                                  
        const part1 = maxNumberFromSingleArray(nums1, i);
        const part2 = maxNumberFromSingleArray(nums2, k - i);
        const candidate = merge(part1, part2);
        if (candidate.join('') > maxNumber.join('')) {
            maxNumber = candidate;
        }
    }
    return maxNumber;   
};
