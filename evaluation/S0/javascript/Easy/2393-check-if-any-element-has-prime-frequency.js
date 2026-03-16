// Source: https://leetcode.com/problems/check-if-any-element-has-prime-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// Return true if the frequency of any element of the array is prime, otherwise, return false.
//
// The frequency of an element x is the number of times it occurs in the array.
//
// A prime number is a natural number greater than 1 with only two factors, 1 and itself.
//
// Example:
// Input: nums = [1,2,3,4,5,4]
//
// Output: true
//
// Explanation:
//
// 4 has a frequency of two, which is a prime number.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var checkPrimeFrequency = function(nums) {
    const frequencyMap = {};
    for (const num of nums) {
        frequencyMap[num] = (frequencyMap[num] || 0) + 1;
    }

    function isPrime(num) {
        if (num <= 1) return false;
        for (let i = 2; i * i <= num; i++) {
            if (num % i === 0) return false;
        }
        return true;
    }

    for (const freq of Object.values(frequencyMap)) {
        if (isPrime(freq)) {
            return true;
        }
    }
    return false;
};