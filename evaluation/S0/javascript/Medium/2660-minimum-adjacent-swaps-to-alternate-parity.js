// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct integers.
//
// In one operation, you can swap any two adjacent elements in the array.
//
// An arrangement of the array is considered valid if the parity of adjacent elements alternates, meaning every pair of neighboring elements consists of one even and one odd number.
//
// Return the minimum number of adjacent swaps required to transform nums into any valid arrangement.
//
// If it is impossible to rearrange nums such that no two adjacent elements have the same parity, return -1.
//
// Example:
// Input: nums = [2,4,6,5,7]
//
// Output: 3
//
// Explanation:
//
// Swapping 5 and 6, the array becomes [2,4,5,6,7]
//
// Swapping 5 and 4, the array becomes [2,5,4,6,7]
//
// Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid arrangement. Thus, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements in nums are distinct.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minSwaps = function(nums) {
    let evenCount = 0;
    for (const num of nums) {
        if (num % 2 === 0) {
            evenCount++;
        }
    }
    const oddCount = nums.length - evenCount;
    if (Math.abs(evenCount - oddCount) > 1) {
        return -1;
    }
    const swaps = (startWithEven) => {
        let swapCount = 0;
        let evenIndex = startWithEven ? 0 : 1;
        let oddIndex = startWithEven ? 1 : 0;
        for (let i = 0; i < nums.length; i++) {
            if (nums[i] % 2 === 0) {
                swapCount += Math.abs(i - evenIndex);
                evenIndex += 2;
            } else {
                swapCount += Math.abs(i - oddIndex);
                oddIndex += 2;
            }
        }
        return swapCount / 2;
    };
    if (evenCount > oddCount) {
        return swaps(true);
    } else if (oddCount > evenCount) {
        return swaps(false);
    } else {
        return Math.min(swaps(true), swaps(false));
    }
};