// Source: https://leetcode.com/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// You can do the following operation on the array at most once:
//
//
// 	Choose any integer x such that nums remains non-empty on removing all occurrences of x.
// 	Remove all occurrences of x from the array.
//
//
// Return the maximum subarray sum across all possible resulting arrays.
//
// Example:
// Input: nums = [-3,2,-2,-1,3,-2,3]
//
// Output: 7
//
// Explanation:
//
// We can have the following arrays after at most one operation:
//
//
// 	The original array is nums = [-3, 2, -2, -1, 3, -2, 3]. The maximum subarray sum is 3 + (-2) + 3 = 4.
// 	Deleting all occurences of x = -3 results in nums = [2, -2, -1, 3, -2, 3]. The maximum subarray sum is 3 + (-2) + 3 = 4.
// 	Deleting all occurences of x = -2 results in nums = [-3, 2, -1, 3, 3]. The maximum subarray sum is 2 + (-1) + 3 + 3 = 7.
// 	Deleting all occurences of x = -1 results in nums = [-3, 2, -2, 3, -2, 3]. The maximum subarray sum is 3 + (-2) + 3 = 4.
// 	Deleting all occurences of x = 3 results in nums = [-3, 2, -2, -1, -2]. The maximum subarray sum is 2.
//
//
// The output is max(4, 4, 7, 4, 2) = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-106 <= nums[i] <= 106
//

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        unordered_map<int, long long> prefixSumMap;
        long long currentSum = 0;
        long long maxSum = LLONG_MIN;

        for (int num : nums) {
            currentSum += num;
            prefixSumMap[num] += num;
            maxSum = max(maxSum, currentSum - prefixSumMap[num]);
            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return maxSum;          
    }
};
