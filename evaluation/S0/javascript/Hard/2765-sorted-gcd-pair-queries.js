// Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and an integer array queries.
//
// Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
//
// For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
//
// Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
//
// The term gcd(a, b) denotes the greatest common divisor of a and b.
//
// Example:
// Input: nums = [2,3,4], queries = [0,2,2]
//
// Output: [1,2,2]
//
// Explanation:
//
// gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
//
// After sorting in ascending order, gcdPairs = [1, 1, 2].
//
// So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	1 <= nums[i] <= 5 * 104
// 	1 <= queries.length <= 105
// 	0 <= queries[i] < n * (n - 1) / 2
//

/**
 * @param {number[]} nums
 * @param {number[]} queries
 * @return {number[]}
 */
var gcdValues = function(nums, queries) {
    const maxNum = Math.max(...nums);
    const freq = new Array(maxNum + 1).fill(0);
    for (const num of nums) {       
        freq[num]++;
    }   
    const countGCD = new Array(maxNum + 1).fill(0);
    for (let g = 1; g <= maxNum; g++) {
        let count = 0;
        for (let multiple = g; multiple <= maxNum; multiple += g) {
            count += freq[multiple];
        }
        if (count >= 2) {
            countGCD[g] = (count * (count - 1)) / 2;
        }
    }
    const prefixCount = new Array(maxNum + 1).fill(0);
    for (let i = 1; i <= maxNum; i++) {
        prefixCount[i] = prefixCount[i - 1] + countGCD[i];
    }
    const results = [];
    for (const query of queries) {
        let left = 1;
        let right = maxNum;
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (prefixCount[mid] > query) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        results.push(left);
    }
    return results;
};
