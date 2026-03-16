// Source: https://leetcode.com/problems/recover-the-original-array/   |   Difficulty: Hard
//
// Problem Description:
// Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:
//
//
// 	lower[i] = arr[i] - k, for every index i where 0 <= i < n
// 	higher[i] = arr[i] + k, for every index i where 0 <= i < n
//
//
// Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.
//
// Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.
//
// Note: The test cases are generated such that there exists at least one valid array arr.
//
// Example:
// Input: nums = [2,10,6,4,8,12]
// Output: [3,7,11]
// Explanation:
// If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
// Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
// Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12].
//
// Constraints:
// 2 * n == nums.length
// 	1 <= n <= 1000
// 	1 <= nums[i] <= 109
// 	The test cases are generated such that there exists at least one valid array arr.
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var recoverArray = function(nums) {
    nums.sort((a, b) => a - b);
    const n = nums.length;
    for (let i = 1; i < n; i += 1) {
        const k = nums[i] - nums[0];
        if (k === 0 || k % 2 !== 0) {
            continue;
        }
        const lower = new Set();
        const higher = new Set();
        for (const num of nums) {
            if (lower.has(num)) {
                lower.delete(num);
            }
            else if (higher.has(num)) {
                higher.delete(num);
            }
            else if (num - k >= 0 && !lower.has(num - k) && !higher.has(num - k)) {
                lower.add(num - k);
            }
            else if (!lower.has(num + k) && !higher.has(num + k)) {
                higher.add(num + k);
            }
            else {
                break;
            }
        }
        if (lower.size === 0 && higher.size === 0) {
            const arr = [];
            for (let j = 0; j < n; j += 2) {
                arr.push(nums[j] + k / 2);
            }
            return arr;
        }
    }
    return [];  
};
