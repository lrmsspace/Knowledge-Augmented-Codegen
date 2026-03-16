// Source: https://leetcode.com/problems/wiggle-sort-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
//
// You may assume the input array always has a valid answer.
//
// Example:
// Input: nums = [1,5,1,1,6,4]
// Output: [1,6,1,5,1,4]
// Explanation: [1,4,1,5,1,6] is also accepted.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	0 <= nums[i] <= 5000
// 	It is guaranteed that there will be an answer for the given input nums.
//
//
//  
// Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?
//

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted(nums);
        sort(sorted.begin(), sorted.end());

        int left = (n - 1) / 2;  // End of the first half
        int right = n - 1;       // End of the second half

        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                nums[i] = sorted[left--];
            } else {
                nums[i] = sorted[right--];
            }
        }           
    }
};
