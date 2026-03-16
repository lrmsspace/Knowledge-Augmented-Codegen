// Source: https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two integers k and numOperations.
//
// You must perform an operation numOperations times on nums, where in each operation you:
//
//
// 	Select an index i that was not selected in any previous operations.
// 	Add an integer in the range [-k, k] to nums[i].
//
//
// Return the maximum possible frequency of any element in nums after performing the operations.
//
// Example:
// Input: nums = [1,4,5], k = 1, numOperations = 2
//
// Output: 2
//
// Explanation:
//
// We can achieve a maximum frequency of two by:
//
//
// 	Adding 0 to nums[1]. nums becomes [1, 4, 5].
// 	Adding -1 to nums[2]. nums becomes [1, 4, 4].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	0 <= k <= 105
// 	0 <= numOperations <= nums.length
//

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        sort(nums.begin(), nums.end());
        int left = 0, maxFreq = 1;
        long long total = 0;

        for (int right = 1; right < nums.size(); ++right) {
            total += (long long)(nums[right] - nums[right - 1]) * (right - left);

            while (total > (long long)k * numOperations) {
                total -= nums[right] - nums[left];
                ++left;
            }

            maxFreq = max(maxFreq, right - left + 1);
        }

        return maxFreq;         
    }
};
