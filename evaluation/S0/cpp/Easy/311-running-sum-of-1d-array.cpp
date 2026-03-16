// Source: https://leetcode.com/problems/running-sum-of-1d-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).
//
// Return the running sum of nums.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: [1,3,6,10]
// Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-10^6 <= nums[i] <= 10^6
//

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> result;
        int running_sum = 0;
        for (int num : nums) {
            running_sum += num;
            result.push_back(running_sum);
        }
        return result;          
    }
};
