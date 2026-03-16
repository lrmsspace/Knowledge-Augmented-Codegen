// Source: https://leetcode.com/problems/sort-array-by-increasing-frequency/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums, sort the array in increasing order based on the frequency of the values. If multiple values have the same frequency, sort them in decreasing order.
//
// Return the sorted array.
//
// Example:
// Input: nums = [1,1,2,2,2,3]
// Output: [3,1,1,2,2,2]
// Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        sort(nums.begin(), nums.end(), [&](int a, int b) {
            if (freq[a] == freq[b]) {
                return a > b; // If frequencies are the same, sort by value in decreasing order
            }
            return freq[a] < freq[b]; // Sort by frequency in increasing order
        });

        return nums;            
    }
};
