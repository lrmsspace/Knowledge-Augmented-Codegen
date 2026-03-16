// Source: https://leetcode.com/problems/target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer target.
//
// You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.
//
//
// 	For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
//
//
// Return the number of different expressions that you can build, which evaluates to target.
//
// Example:
// Input: nums = [1,1,1,1,1], target = 3
// Output: 5
// Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
//
// Constraints:
// 1 <= nums.length <= 20
// 	0 <= nums[i] <= 1000
// 	0 <= sum(nums[i]) <= 1000
// 	-1000 <= target <= 1000
//

int findTargetSumWays(int* nums, int numsSize, int target) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    // Check if (sum + target) is even and non-negative
    if ((sum + target) % 2 != 0 || sum < abs(target)) {
        return 0;
    }

    int subsetSum = (sum + target) / 2;

    // Initialize DP array
    int dp[subsetSum + 1];
    for (int i = 0; i <= subsetSum; i++) {
        dp[i] = 0;
    }
    dp[0] = 1; // There's one way to make sum 0

    // Fill the DP array
    for (int i = 0; i < numsSize; i++) {
        for (int j = subsetSum; j >= nums[i]; j--) {
            dp[j] += dp[j - nums[i]];
        }
    }

    return dp[subsetSum];       
}
