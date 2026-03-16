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

int minimumOperations(int* nums, int numsSize) {
    int count[4] = {0};
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int dp[4][4];
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            dp[i][j] = dp[i][j - 1];
            if (nums[j - 1] == i) {
                dp[i][j]++;
            }
        }
    }

    int maxKeep = 0;
    for (int i = 0; i <= count[1]; i++) {
        for (int j = 0; j <= count[2]; j++) {
            int keep = dp[1][i] + (dp[2][i + j] - dp[2][i]) + (dp[3][numsSize] - dp[3][i + j]);
            if (keep > maxKeep) {
                maxKeep = keep;
            }
        }
    }

    return numsSize - maxKeep;      
}
