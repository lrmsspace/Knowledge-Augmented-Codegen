// Source: https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is the number of pivot indices that satisfy both conditions:
//
//
// 	1 <= pivot < n
// 	nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
//
//
// You are also given an integer k. You can choose to change the value of one element of nums to k, or to leave the array unchanged.
//
// Return the maximum possible number of ways to partition nums to satisfy both conditions after changing at most one element.
//
// Example:
// Input: nums = [2,-1,2], k = 3
// Output: 1
// Explanation: One optimal approach is to change nums[0] to k. The array becomes [3,-1,2].
// There is one way to partition the array:
// - For pivot = 2, we have the partition [3,-1 | 2]: 3 + -1 == 2.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	-105 <= k, nums[i] <= 105
//

class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        
        unordered_map<long long, int> leftCount, rightCount;
        for (int pivot = 1; pivot < n; pivot++) {
            long long leftSum = prefixSum[pivot];
            long long rightSum = prefixSum[n] - prefixSum[pivot];
            if (leftSum == rightSum) {
                rightCount[leftSum]++;
            }
        }
        
        int maxWays = 0;
        for (const auto& entry : rightCount) {
            maxWays = max(maxWays, entry.second);
        }
        
        for (int i = 0; i < n; i++) {
            long long diff = k - nums[i];
            int currentWays = 0;
            
            // Update left counts
            if (i > 0) {
                long long leftTarget = prefixSum[i] + diff;
                if (leftCount.count(leftTarget)) {
                    currentWays += leftCount[leftTarget];
                }
            }
            
            // Update right counts
            if (i < n - 1) {
                long long rightTarget = prefixSum[n] - prefixSum[i + 1] - diff;
                if (rightCount.count(rightTarget)) {
                    currentWays += rightCount[rightTarget];
                }
            }
            
            maxWays = max(maxWays, currentWays);
            
            // Move pivot from right to left
            if (i + 1 < n) {
                long long leftSum = prefixSum[i + 1];
                long long rightSum = prefixSum[n] - prefixSum[i + 1];
                if (leftSum == rightSum) {
                    rightCount[leftSum]--;
                    if (rightCount[leftSum] == 0) {
                        rightCount.erase(leftSum);
                    }
                    leftCount[leftSum]++;
                }
            }
        }
        
        return maxWays;         
    }
};
