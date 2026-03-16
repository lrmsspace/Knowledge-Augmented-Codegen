// Source: https://leetcode.com/problems/find-if-digit-game-can-be-won/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of positive integers nums.
//
// Alice and Bob are playing a game. In the game, Alice can choose either all single-digit numbers or all double-digit numbers from nums, and the rest of the numbers are given to Bob. Alice wins if the sum of her numbers is strictly greater than the sum of Bob's numbers.
//
// Return true if Alice can win this game, otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,4,10]
//
// Output: false
//
// Explanation:
//
// Alice cannot win by choosing either single-digit or double-digit numbers.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 99
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var canAliceWin = function(nums) {
    let singleDigitSum = 0;
    let doubleDigitSum = 0;
    for (const num of nums) {
        if (num < 10) {
            singleDigitSum += num;
        } else {
            doubleDigitSum += num;
        }
    }
    const totalSum = singleDigitSum + doubleDigitSum;
    return singleDigitSum > totalSum - singleDigitSum || doubleDigitSum > totalSum - doubleDigitSum;
};