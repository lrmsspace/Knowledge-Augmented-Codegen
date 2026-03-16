// Source: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.
//
// Example:
// Input: nums = [4,3,2,3,5,2,1], k = 4
// Output: true
// Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	1 <= nums[i] <= 104
// 	The frequency of each element is in the range [1, 4].
//

bool canPartitionKSubsets(int* nums, int numsSize, int k) {
    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }
    
    if (totalSum % k != 0) {
        return false;
    }
    
    int targetSum = totalSum / k;
    bool* used = (bool*)calloc(numsSize, sizeof(bool));
    
    bool backtrack(int startIndex, int numberOfSubsets, int currentSum) {
        if (numberOfSubsets == 0) {
            return true;
        }
        
        if (currentSum == targetSum) {
            return backtrack(0, numberOfSubsets - 1, 0);
        }
        
        for (int i = startIndex; i < numsSize; i++) {
            if (!used[i] && currentSum + nums[i] <= targetSum) {
                used[i] = true;
                if (backtrack(i + 1, numberOfSubsets, currentSum + nums[i])) {
                    return true;
                }
                used[i] = false;
            }
        }
        
        return false;
    }
    
    bool result = backtrack(0, k, 0);
    free(used);
    return result;      
}
