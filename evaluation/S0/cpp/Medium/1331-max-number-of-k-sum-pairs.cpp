// Source: https://leetcode.com/problems/max-number-of-k-sum-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.
//
// Return the maximum number of operations you can perform on the array.
//
// Example:
// Input: nums = [1,2,3,4], k = 5
// Output: 2
// Explanation: Starting with nums = [1,2,3,4]:
// - Remove numbers 1 and 4, then nums = [2,3]
// - Remove numbers 2 and 3, then nums = []
// There are no more pairs that sum up to 5, hence a total of 2 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> countMap;
        int operations = 0;

        for (int num : nums) {
            int complement = k - num;
            if (countMap[complement] > 0) {
                operations++;
                countMap[complement]--;
            } else {
                countMap[num]++;
            }
        }

        return operations;          
    }
};
