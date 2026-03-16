// Source: https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Some values in nums are missing and are denoted by -1.
//
// You must choose a pair of positive integers (x, y) exactly once and replace each missing element with either x or y.
//
// You need to minimize the maximum absolute difference between adjacent elements of nums after replacements.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [1,2,-1,10,8]
//
// Output: 4
//
// Explanation:
//
// By choosing the pair as (6, 7), nums can be changed to [1, 2, 6, 10, 8].
//
// The absolute differences between adjacent elements are:
//
//
// 	|1 - 2| == 1
// 	|2 - 6| == 4
// 	|6 - 10| == 4
// 	|10 - 8| == 2
//
// Constraints:
// 2 <= nums.length <= 105
// 	nums[i] is either -1 or in the range [1, 109].
//

class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        int left = INT_MAX, right = INT_MIN;
        
        // Find min and max of known elements adjacent to -1
        for (int i = 0; i < n; i++) {
            if (nums[i] == -1) {
                if (i > 0 && nums[i - 1] != -1) {
                    left = min(left, nums[i - 1]);
                    right = max(right, nums[i - 1]);
                }
                if (i < n - 1 && nums[i + 1] != -1) {
                    left = min(left, nums[i + 1]);
                    right = max(right, nums[i + 1]);
                }
            }
        }
        
        // If there are no known elements adjacent to -1
        if (left == INT_MAX) {
            return 0;
        }
        
        int mid = left + (right - left) / 2;
        int maxDiff = 0;
        
        // Calculate maximum adjacent difference after replacement
        for (int i = 0; i < n - 1; i++) {
            int a = (nums[i] == -1) ? mid : nums[i];
            int b = (nums[i + 1] == -1) ? mid : nums[i + 1];
            maxDiff = max(maxDiff, abs(a - b));
        }
        
        return maxDiff;         
    }
};
