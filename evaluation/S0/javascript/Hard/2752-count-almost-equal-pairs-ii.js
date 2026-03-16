// Source: https://leetcode.com/problems/count-almost-equal-pairs-ii/   |   Difficulty: Hard
//
// Problem Description:
// Attention: In this version, the number of operations that can be performed, has been increased to twice.
//
// You are given an array nums consisting of positive integers.
//
// We call two integers x and y almost equal if both integers can become equal after performing the following operation at most twice:
//
//
// 	Choose either x or y and swap any two digits within the chosen number.
//
//
// Return the number of indices i and j in nums where i < j such that nums[i] and nums[j] are almost equal.
//
// Note that it is allowed for an integer to have leading zeros after performing an operation.
//
// Example:
// Input: nums = [1023,2310,2130,213]
//
// Output: 4
//
// Explanation:
//
// The almost equal pairs of elements are:
//
//
// 	1023 and 2310. By swapping the digits 1 and 2, and then the digits 0 and 3 in 1023, you get 2310.
// 	1023 and 213. By swapping the digits 1 and 0, and then the digits 1 and 2 in 1023, you get 0213, which is 213.
// 	2310 and 213. By swapping the digits 2 and 0, and then the digits 3 and 2 in 2310, you get 0213, which is 213.
// 	2310 and 2130. By swapping the digits 3 and 1 in 2310, you get 2130.
//
// Constraints:
// 2 <= nums.length <= 5000
// 	1 <= nums[i] < 107
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countPairs = function(nums) {
    const countMap = new Map();
    for (const num of nums) {
        const digitCount = Array(10).fill(0);
        let temp = num;
        while (temp > 0) {
            digitCount[temp % 10]++;
            temp = Math.floor(temp / 10);
        }
        const key = digitCount.join('#');
        countMap.set(key, (countMap.get(key) || 0) + 1);
    }
    let result = 0;
    for (const count of countMap.values()) {
        result += (count * (count - 1)) / 2;
    }
    return result;  
};
