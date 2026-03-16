// Source: https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// You are allowed to delete any number of elements from nums without making it empty. After performing the deletions, select a subarray of nums such that:
//
//
// 	All elements in the subarray are unique.
// 	The sum of the elements in the subarray is maximized.
//
//
// Return the maximum sum of such a subarray.
//
// Example:
// Input: nums = [1,2,3,4,5]
//
// Output: 15
//
// Explanation:
//
// Select the entire array without deleting any element to obtain the maximum sum.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

class Solution {
public:
    int maxSum(vector<int>& nums) {
        int n = nums.size();
        int maxSum = INT_MIN;

        for (int i = 0; i < n; ++i) {
            unordered_set<int> seen;
            int currentSum = 0;

            for (int j = i; j < n; ++j) {
                if (seen.find(nums[j]) != seen.end()) {
                    break; // Duplicate found, stop expanding the subarray
                }

                seen.insert(nums[j]);
                currentSum += nums[j];
                maxSum = max(maxSum, currentSum);
            }
        }

        return maxSum;          
    }
};
