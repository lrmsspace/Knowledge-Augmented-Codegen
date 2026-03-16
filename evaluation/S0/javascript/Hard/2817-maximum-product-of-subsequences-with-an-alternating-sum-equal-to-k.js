// Source: https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers, k and limit. Your task is to find a non-empty subsequence of nums that:
//
//
// 	Has an alternating sum equal to k.
// 	Maximizes the product of all its numbers without the product exceeding limit.
//
//
// Return the product of the numbers in such a subsequence. If no subsequence satisfies the requirements, return -1.
//
// The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
//
// Example:
// Input: nums = [1,2,3], k = 2, limit = 10
//
// Output: 6
//
// Explanation:
//
// The subsequences with an alternating sum of 2 are:
//
//
// 	[1, 2, 3]
//
// 	
// 		Alternating Sum: 1 - 2 + 3 = 2
// 		Product: 1 * 2 * 3 = 6
// 	
// 	
// 	[2]
// 	
// 		Alternating Sum: 2
// 		Product: 2
// 	
// 	
//
//
// The maximum product within the limit is 6.
//
// Constraints:
// 1 <= nums.length <= 150
// 	0 <= nums[i] <= 12
// 	-105 <= k <= 105
// 	1 <= limit <= 5000
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} limit
 * @return {number}
 */
var maxProduct = function(nums, k, limit) {
    const n = nums.length;
    const dp = Array.from({ length: n + 1 }, () => new Map());
    dp[0].set(0, 1);
    for (let i = 1; i <= n; i++) {
        const num = nums[i - 1];
        for (const [altSum, prod] of dp[i - 1]) {
            // Exclude nums[i - 1]
            if (!dp[i].has(altSum) || dp[i].get(altSum) < prod) {
                dp[i].set(altSum, prod);
            }
            // Include nums[i - 1] at even index
            const newAltSumEven = altSum + num;
            const newProdEven = prod * num;
            if (newProdEven <= limit) {
                if (!dp[i].has(newAltSumEven) || dp[i].get(newAltSumEven) < newProdEven) {
                    dp[i].set(newAltSumEven, newProdEven);
                }
            }
            // Include nums[i - 1] at odd index
            const newAltSumOdd = altSum - num;
            const newProdOdd = prod * num;
            if (newProdOdd <= limit) {
                if (!dp[i].has(newAltSumOdd) || dp[i].get(newAltSumOdd) < newProdOdd) {
                    dp[i].set(newAltSumOdd, newProdOdd);
                }
            }
        }
    }
    return dp[n].has(k) ? dp[n].get(k) : -1;
};
