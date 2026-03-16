// Source: https://leetcode.com/problems/number-of-different-subsequences-gcds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums that consists of positive integers.
//
// The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.
//
//
// 	For example, the GCD of the sequence [4,6,16] is 2.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// Return the number of different GCDs among all non-empty subsequences of nums.
//
// Example:
// Input: nums = [6,10,3]
// Output: 5
// Explanation: The figure shows all the non-empty subsequences and their GCDs.
// The different GCDs are 6, 10, 3, 2, and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 2 * 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countDifferentSubsequenceGCDs = function(nums) {
    const maxNum = Math.max(...nums);
    const present = new Array(maxNum + 1).fill(false);
    for (const num of nums) {
        present[num] = true;
    }
    let count = 0;
    for (let gcd = 1; gcd <= maxNum; gcd++) {
        let currentGCD = 0;
        for (let multiple = gcd; multiple <= maxNum; multiple += gcd) {
            if (present[multiple]) {
                currentGCD = gcd(currentGCD, multiple);
                if (currentGCD === gcd) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
};

function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
}