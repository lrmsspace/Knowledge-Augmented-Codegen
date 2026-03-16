// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. In one operation, you can replace any element in nums with any integer.
//
// nums is considered continuous if both of the following conditions are fulfilled:
//
//
// 	All elements in nums are unique.
// 	The difference between the maximum element and the minimum element in nums equals nums.length - 1.
//
//
// For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.
//
// Return the minimum number of operations to make nums continuous.
//
// Example:
// Input: nums = [4,2,5,3]
// Output: 0
// Explanation: nums is already continuous.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int minOperations(vector<int>& nums) {
        set<int> uniqueNums(nums.begin(), nums.end());
        vector<int> sortedNums(uniqueNums.begin(), uniqueNums.end());
        int n = nums.size();
        int m = sortedNums.size();
        
        int minOps = n;  // Start with the worst case: change all elements
        int left = 0;
        
        for (int right = 0; right < m; ++right) {
            // Expand the window to include sortedNums[right]
            while (sortedNums[right] - sortedNums[left] >= n) {
                left++;  // Shrink from the left
            }
            // Calculate the number of operations needed
            int currentWindowSize = right - left + 1;
            minOps = min(minOps, n - currentWindowSize);
        }
        
        return minOps;          
    }
};
