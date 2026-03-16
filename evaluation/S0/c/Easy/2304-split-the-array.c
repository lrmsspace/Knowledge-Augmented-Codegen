// Source: https://leetcode.com/problems/split-the-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums of even length. You have to split the array into two parts nums1 and nums2 such that:
//
//
// 	nums1.length == nums2.length == nums.length / 2.
// 	nums1 should contain distinct elements.
// 	nums2 should also contain distinct elements.
//
//
// Return true if it is possible to split the array, and false otherwise.
//
// Example:
// Input: nums = [1,1,2,2,3,4]
// Output: true
// Explanation: One of the possible ways to split nums is nums1 = [1,2,3] and nums2 = [1,2,4].
//
// Constraints:
// 1 <= nums.length <= 100
// 	nums.length % 2 == 0 
// 	1 <= nums[i] <= 100
//

bool isPossibleToSplit(int* nums, int numsSize) {
    int freq[101] = {0};
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
        if (freq[nums[i]] > 2) {
            return false;
        }
    }
    return true;        
}
