// Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
//
// Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
//
// Return the median of the uniqueness array of nums.
//
// Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 1
//
// Explanation:
//
// The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> freq(100005, 0);
        long long totalSubarrays = (long long)n * (n + 1) / 2;
        long long medianPos = (totalSubarrays + 1) / 2;
        long long count = 0;
        int left = 0, right = 0;
        int distinctCount = 0;

        while (right < n) {
            freq[nums[right]]++;
            if (freq[nums[right]] == 1) {
                distinctCount++;
            }

            while (count + (right - left + 1) >= medianPos) {
                if (count + (right - left + 1) == medianPos) {
                    return distinctCount;
                }
                freq[nums[left]]--;
                if (freq[nums[left]] == 0) {
                    distinctCount--;
                }
                count += (right - left + 1);
                left++;
            }
            right++;
        }

        return -1; // This line should never be reached         
    }
};
