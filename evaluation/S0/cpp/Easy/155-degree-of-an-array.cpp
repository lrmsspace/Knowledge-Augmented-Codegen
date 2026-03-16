// Source: https://leetcode.com/problems/degree-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
//
// Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
//
// Example:
// Input: nums = [1,2,2,3,1]
// Output: 2
// Explanation: 
// The input array has a degree of 2 because both elements 1 and 2 appear twice.
// Of the subarrays that have the same degree:
// [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
// The shortest length is 2. So return 2.
//
// Constraints:
// nums.length will be between 1 and 50,000.
// 	nums[i] will be an integer between 0 and 49,999.
//

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> firstIndex, count;
        int degree = 0, minLength = nums.size();

        for (int i = 0; i < nums.size(); ++i) {
            if (firstIndex.find(nums[i]) == firstIndex.end()) {
                firstIndex[nums[i]] = i;
            }
            count[nums[i]]++;

            if (count[nums[i]] > degree) {
                degree = count[nums[i]];
                minLength = i - firstIndex[nums[i]] + 1;
            } else if (count[nums[i]] == degree) {
                minLength = min(minLength, i - firstIndex[nums[i]] + 1);
            }
        }

        return minLength;           
    }
};
