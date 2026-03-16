// Source: https://leetcode.com/problems/split-the-array-to-make-coprime-products/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n.
//
// A split at an index i where 0 <= i <= n - 2 is called valid if the product of the first i + 1 elements and the product of the remaining elements are coprime.
//
//
// 	For example, if nums = [2, 3, 3], then a split at the index i = 0 is valid because 2 and 9 are coprime, while a split at the index i = 1 is not valid because 6 and 3 are not coprime. A split at the index i = 2 is not valid because i == n - 1.
//
//
// Return the smallest index i at which the array can be split validly or -1 if there is no such split.
//
// Two values val1 and val2 are coprime if gcd(val1, val2) == 1 where gcd(val1, val2) is the greatest common divisor of val1 and val2.
//
// Example:
// Input: nums = [4,7,8,15,3,5]
// Output: 2
// Explanation: The table above shows the values of the product of the first i + 1 elements, the remaining elements, and their gcd at each index i.
// The only valid split is at index 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 104
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findValidSplit = function(nums) {
    const n = nums.length;
    const maxNum = Math.max(...nums);
    const primeFactors = Array.from({ length: maxNum + 1 }, () => []);
    for (let i = 2; i <= maxNum; i++) {
        if (primeFactors[i].length === 0) {
            for (let j = i; j <= maxNum; j += i) {
                primeFactors[j].push(i);
            }
        }
    }

    const leftFactors = new Set();
    const rightFactors = new Set();
    for (const num of nums) {
        for (const factor of primeFactors[num]) {
            rightFactors.add(factor);
        }
    }

    for (let i = 0; i < n - 1; i++) {
        for (const factor of primeFactors[nums[i]]) {
            leftFactors.add(factor);
            rightFactors.delete(factor);
        }
        if (leftFactors.size === 0 || rightFactors.size === 0) {
            continue;
        }
        let isCoprime = true;
        for (const factor of leftFactors) {
            if (rightFactors.has(factor)) {
                isCoprime = false;
                break;
            }
        }
        if (isCoprime) {
            return i;
        }
    }
    return -1;
};
