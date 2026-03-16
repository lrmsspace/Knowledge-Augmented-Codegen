// Source: https://leetcode.com/problems/count-the-number-of-good-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of good subarrays of nums.
//
// A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1,1,1], k = 10
// Output: 1
// Explanation: The only good subarray is the array nums itself.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 109
//

class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long left = 0, right = 0;
        long long count = 0;
        long long result = 0;
        unordered_map<int, long long> freq;

        while (right < nums.size()) {
            count += freq[nums[right]];
            freq[nums[right]]++;
            right++;

            while (count >= k) {
                result += nums.size() - right + 1;
                freq[nums[left]]--;
                count -= freq[nums[left]];
                left++;
            }
        }

        return result;          
    }
};
