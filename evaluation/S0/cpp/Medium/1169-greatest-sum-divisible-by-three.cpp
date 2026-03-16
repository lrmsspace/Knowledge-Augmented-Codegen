// Source: https://leetcode.com/problems/greatest-sum-divisible-by-three/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.
//
// Example:
// Input: nums = [3,6,5,1,8]
// Output: 18
// Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
//
// Constraints:
// 1 <= nums.length <= 4 * 104
// 	1 <= nums[i] <= 104
//

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        if (totalSum % 3 == 0) {
            return totalSum;
        }

        // Remainder buckets
        vector<vector<int>> remainderBuckets(3);
        for (int num : nums) {
            remainderBuckets[num % 3].push_back(num);
        }

        // Sort the buckets to easily access the smallest elements
        for (auto& bucket : remainderBuckets) {
            sort(bucket.begin(), bucket.end());
        }

        int remainder = totalSum % 3;
        int option1 = INT_MIN, option2 = INT_MIN;

        // Option 1: Remove the smallest element with the same remainder
        if (!remainderBuckets[remainder].empty()) {
            option1 = totalSum - remainderBuckets[remainder][0];
        }

        // Option 2: Remove two smallest elements with the other remainder
        int otherRemainder = (3 - remainder) % 3;
        if (remainderBuckets[otherRemainder].size() >= 2) {
            option2 = totalSum - remainderBuckets[otherRemainder][0] - remainderBuckets[otherRemainder][1];
        }

        return max(option1, option2);           
    }
};
