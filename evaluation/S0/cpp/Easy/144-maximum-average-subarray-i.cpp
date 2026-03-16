// Source: https://leetcode.com/problems/maximum-average-subarray-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums consisting of n elements, and an integer k.
//
// Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.
//
// Example:
// Input: nums = [1,12,-5,-6,50,3], k = 4
// Output: 12.75000
// Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
//
// Constraints:
// n == nums.length
// 	1 <= k <= n <= 105
// 	-104 <= nums[i] <= 104
//

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double maxAvg = INT_MIN;
        double windowSum = 0.0;
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {
            windowSum += nums[right];

            if (right - left + 1 == k) {
                double currentAvg = windowSum / k;
                maxAvg = max(maxAvg, currentAvg);
                windowSum -= nums[left];
                left++;
            }
        }

        return maxAvg;          
    }
};
