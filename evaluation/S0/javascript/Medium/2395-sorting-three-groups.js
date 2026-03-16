// Source: https://leetcode.com/problems/sorting-three-groups/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. Each element in nums is 1, 2 or 3. In each operation, you can remove an element from nums. Return the minimum number of operations to make nums non-decreasing.
//
// Example:
// Input: nums = [2,1,3,2,1]
//
// Output: 3
//
// Explanation:
//
// One of the optimal solutions is to remove nums[0], nums[2] and nums[3].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 3
//
//
//  
// Follow-up: Can you come up with an algorithm that runs in O(n) time complexity?
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumOperations = function(nums) {
    const n = nums.length;
    const count = [0, 0, 0];
    for (const num of nums) {
        count[num - 1]++;
    }
    const dp = Array.from({ length: n + 1 }, () => Array(3).fill(Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < 3; j++) {
            dp[i][j] = dp[i - 1][j] + (nums[i - 1] !== j + 1 ? 1 : 0);
            if (j > 0) {
                dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1] + (nums[i - 1] !== j + 1 ? 1 : 0));
            }
        }
    }   
    return Math.min(dp[n][0], dp[n][1], dp[n][2]);  
};
