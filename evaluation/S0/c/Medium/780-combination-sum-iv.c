// Source: https://leetcode.com/problems/combination-sum-iv/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.
//
// The test cases are generated so that the answer can fit in a 32-bit integer.
//
// Example:
// Input: nums = [1,2,3], target = 4
// Output: 7
// Explanation:
// The possible combination ways are:
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)
// Note that different sequences are counted as different combinations.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 1000
// 	All the elements of nums are unique.
// 	1 <= target <= 1000
//
//
//  
// Follow up: What if negative numbers are allowed in the given array? How does it change the problem? What limitation we need to add to the question to allow negative numbers?
//

int combinationSum4(int* nums, int numsSize, int target) {
    int dp[target + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= target; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (i - nums[j] >= 0) {
                dp[i] += dp[i - nums[j]];
            }
        }
    }

    return dp[target];      
}
