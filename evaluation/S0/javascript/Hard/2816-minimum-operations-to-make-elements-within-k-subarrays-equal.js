// Source: https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):
//
//
// 	Increase or decrease any element of nums by 1.
//
//
// Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, where all elements within each subarray are equal.
//
// Example:
// Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
//
// Output: 8
//
// Explanation:
//
//
// 	Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
// 	Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
// 	Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.
//
// Constraints:
// 2 <= nums.length <= 105
// 	-106 <= nums[i] <= 106
// 	2 <= x <= nums.length
// 	1 <= k <= 15
// 	2 <= k * x <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} x
 * @param {number} k
 * @return {number}
 */
var minOperations = function(nums, x, k) {
    const n = nums.length;
    const dp = Array.from({ length: n + 1 }, () => Array(k + 1).fill(Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][j];
            if (i >= x && j > 0) {
                const subarray = nums.slice(i - x, i).sort((a, b) => a - b);
                const median = subarray[Math.floor(x / 2)];
                let cost = 0;
                for (const num of subarray) {   
                    cost += Math.abs(num - median);
                }
                dp[i][j] = Math.min(dp[i][j], dp[i - x][j - 1] + cost);
            }
        }
    }
    return dp[n][k] === Infinity ? -1 : dp[n][k];
};
