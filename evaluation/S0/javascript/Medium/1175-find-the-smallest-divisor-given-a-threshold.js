// Source: https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it, and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.
//
// Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).
//
// The test cases are generated so that there will be an answer.
//
// Example:
// Input: nums = [1,2,5,9], threshold = 6
// Output: 5
// Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
// If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2).
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 106
// 	nums.length <= threshold <= 106
//

/**
 * @param {number[]} nums
 * @param {number} threshold
 * @return {number}
 */
var smallestDivisor = function(nums, threshold) {
    const getSum = (divisor) => {
        let sum = 0;
        for (const num of nums) {
            sum += Math.ceil(num / divisor);
        }
        return sum;
    };

    let left = 1, right = Math.max(...nums);
    let result = right;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const currentSum = getSum(mid);
        if (currentSum <= threshold) {  
            result = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return result;  
            
};
