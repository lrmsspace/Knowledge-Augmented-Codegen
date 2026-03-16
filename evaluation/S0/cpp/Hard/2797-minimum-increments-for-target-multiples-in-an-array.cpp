// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//

class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        int m = target.size();
        vector<int> increments(n, INT_MAX);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int t = target[j];
                int num = nums[i];
                int inc = (t - (num % t)) % t;
                increments[i] = min(increments[i], inc);
            }
        }
        
        sort(increments.begin(), increments.end());
        
        int result = 0;
        for (int i = 0; i < m; i++) {
            result += increments[i];
        }
        
        return result;          
    }
};
