// Source: https://leetcode.com/problems/sum-of-even-numbers-after-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an array queries where queries[i] = [vali, indexi].
//
// For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even values of nums.
//
// Return an integer array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
// Output: [8,6,2,4]
// Explanation: At the beginning, the array is [1,2,3,4].
// After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
// After adding -3 to nums[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
// After adding -4 to nums[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
// After adding 2 to nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-104 <= nums[i] <= 104
// 	1 <= queries.length <= 104
// 	-104 <= vali <= 104
// 	0 <= indexi < nums.length
//

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var sumEvenAfterQueries = function(nums, queries) {
    let evenSum = 0;
    const result = [];
    // Calculate initial sum of even numbers
    for (const num of nums) {
        if (num % 2 === 0) {
            evenSum += num;
        }
    }
    for (const [val, index] of queries) {
        const oldValue = nums[index];
        const newValue = oldValue + val;
        nums[index] = newValue;
        // Update evenSum based on old and new values
        if (oldValue % 2 === 0) {
            evenSum -= oldValue;
        }
        if (newValue % 2 === 0) {
            evenSum += newValue;
        }
        result.push(evenSum);
    }
    return result;
        
};
