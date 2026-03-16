// Source: https://leetcode.com/problems/first-missing-positive/   |   Difficulty: Hard
//
// Problem Description:
// Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.
//
// You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.
//
// Example:
// Input: nums = [1,2,0]
// Output: 3
// Explanation: The numbers in the range [1,2] are all in the array.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
//

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        
        return n + 1;           
    }
};
