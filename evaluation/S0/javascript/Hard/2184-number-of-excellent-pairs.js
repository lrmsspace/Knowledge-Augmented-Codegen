// Source: https://leetcode.com/problems/number-of-excellent-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed positive integer array nums and a positive integer k.
//
// A pair of numbers (num1, num2) is called excellent if the following conditions are satisfied:
//
//
// 	Both the numbers num1 and num2 exist in the array nums.
// 	The sum of the number of set bits in num1 OR num2 and num1 AND num2 is greater than or equal to k, where OR is the bitwise OR operation and AND is the bitwise AND operation.
//
//
// Return the number of distinct excellent pairs.
//
// Two pairs (a, b) and (c, d) are considered distinct if either a != c or b != d. For example, (1, 2) and (2, 1) are distinct.
//
// Note that a pair (num1, num2) such that num1 == num2 can also be excellent if you have at least one occurrence of num1 in the array.
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: 5
// Explanation: The excellent pairs are the following:
// - (3, 3). (3 AND 3) and (3 OR 3) are both equal to (11) in binary. The total number of set bits is 2 + 2 = 4, which is greater than or equal to k = 3.
// - (2, 3) and (3, 2). (2 AND 3) is equal to (10) in binary, and (2 OR 3) is equal to (11) in binary. The total number of set bits is 1 + 2 = 3.
// - (1, 3) and (3, 1). (1 AND 3) is equal to (01) in binary, and (1 OR 3) is equal to (11) in binary. The total number of set bits is 1 + 2 = 3.
// So the number of excellent pairs is 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 60
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countExcellentPairs = function(nums, k) {
    const uniqueNums = [...new Set(nums)];
    const bitCount = uniqueNums.map(num => num.toString(2).split('0').join('').length);
    const countMap = new Map();
    for (const count of bitCount) {
        countMap.set(count, (countMap.get(count) || 0) + 1);
    }
    let result = 0;
    for (const [count1, freq1] of countMap) {
        for (const [count2, freq2] of countMap) {
            if (count1 + count2 >= k) {
                result += freq1 * freq2;
            }
        }
    }
    return result;  
};
