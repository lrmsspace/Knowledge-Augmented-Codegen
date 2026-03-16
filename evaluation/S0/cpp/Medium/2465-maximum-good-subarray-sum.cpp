// Source: https://leetcode.com/problems/maximum-good-subarray-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of length n and a positive integer k.
//
// A subarray of nums is called good if the absolute difference between its first and last element is exactly k, in other words, the subarray nums[i..j] is good if |nums[i] - nums[j]| == k.
//
// Return the maximum sum of a good subarray of nums. If there are no good subarrays, return 0.
//
// Example:
// Input: nums = [1,2,3,4,5,6], k = 1
// Output: 11
// Explanation: The absolute difference between the first and last element must be 1 for a good subarray. All the good subarrays are: [1,2], [2,3], [3,4], [4,5], and [5,6]. The maximum subarray sum is 11 for the subarray [5,6].
//
// Constraints:
// 2 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= k <= 109
//

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long maxSum = 0;
        long long currentSum = 0;
        int left = 0;

        for (int right = 0; right < nums.size(); ++right) {
            currentSum += nums[right];

            while (left < right && abs(nums[right] - nums[left]) > k) {
                currentSum -= nums[left];
                ++left;
            }

            if (abs(nums[right] - nums[left]) == k) {
                maxSum = max(maxSum, currentSum);
            }
        }

        return maxSum;          
    }
};
