// Source: https://leetcode.com/problems/closest-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer goal.
//
// You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
//
// Return the minimum possible value of abs(sum - goal).
//
// Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
//
// Example:
// Input: nums = [5,-7,3,5], goal = 6
// Output: 0
// Explanation: Choose the whole array as a subsequence, with a sum of 6.
// This is equal to the goal, so the absolute difference is 0.
//
// Constraints:
// 1 <= nums.length <= 40
// 	-107 <= nums[i] <= 107
// 	-109 <= goal <= 109
//

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        unordered_set<int> leftSums, rightSums;
        
        // Generate all possible sums for the left half
        int leftSize = n / 2;
        for (int mask = 0; mask < (1 << leftSize); mask++) {
            int sum = 0;
            for (int i = 0; i < leftSize; i++) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                }
            }
            leftSums.insert(sum);
        }
        
        // Generate all possible sums for the right half
        int rightSize = n - leftSize;
        for (int mask = 0; mask < (1 << rightSize); mask++) {
            int sum = 0;
            for (int i = 0; i < rightSize; i++) {
                if (mask & (1 << i)) {
                    sum += nums[leftSize + i];
                }
            }
            rightSums.insert(sum);
        }
        
        // Convert rightSums to a sorted vector for binary search
        vector<int> rightVec(rightSums.begin(), rightSums.end());
        sort(rightVec.begin(), rightVec.end());
        
        int minDiff = abs(goal);  // Start with the case of empty subsequence
        
        // For each sum in leftSums, find the best match in rightSums
        for (int leftSum : leftSums) {
            int target = goal - leftSum;
            
            // Binary search in rightVec
            auto it = lower_bound(rightVec.begin(), rightVec.end(), target);
            
            // Check the found position
            if (it != rightVec.end()) {
                minDiff = min(minDiff, abs(leftSum + *it - goal));
            }
            if (it != rightVec.begin()) {
                --it;
                minDiff = min(minDiff, abs(leftSum + *it - goal));
            }
        }
        
        return minDiff;         
    }
};
