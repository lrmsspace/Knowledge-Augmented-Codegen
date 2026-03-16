// Source: https://leetcode.com/problems/count-beautiful-splits-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums.
//
// A split of an array nums is beautiful if:
//
//
// 	The array nums is split into three subarrays: nums1, nums2, and nums3, such that nums can be formed by concatenating nums1, nums2, and nums3 in that order.
// 	The subarray nums1 is a prefix of nums2 OR nums2 is a prefix of nums3.
//
//
// Return the number of ways you can make this split.
//
// Example:
// Input: nums = [1,1,2,1]
//
// Output: 2
//
// Explanation:
//
// The beautiful splits are:
//
//
// 	A split with nums1 = [1], nums2 = [1,2], nums3 = [1].
// 	A split with nums1 = [1], nums2 = [1], nums3 = [2,1].
//
// Constraints:
// 1 <= nums.length <= 5000
// 	0 <= nums[i] <= 50
//

int beautifulSplits(int* nums, int numsSize) {
    int count = 0;
    for (int i = 1; i < numsSize - 1; i++) {
        // Check if nums1 is a prefix of nums2
        int isPrefix1 = 1;
        for (int j = 0; j < i; j++) {
            if (nums[j] != nums[i + j]) {
                isPrefix1 = 0;
                break;
            }
        }
        if (isPrefix1) {
            count++;
        }

        // Check if nums2 is a prefix of nums3
        int isPrefix2 = 1;
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[i + j] != nums[i + j + 1]) {
                isPrefix2 = 0;
                break;
            }
        }
        if (isPrefix2) {
            count++;
        }
    }
    return count;       
}
