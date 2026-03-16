// Source: https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. A sequence of integers seq is called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].
//
// Return the maximum possible length of a good subsequence of nums.
//
// Example:
// Input: nums = [1,2,1,1,3], k = 2
//
// Output: 4
//
// Explanation:
//
// The maximum length subsequence is [1,2,1,1,3].
//
// Constraints:
// 1 <= nums.length <= 500
// 	1 <= nums[i] <= 109
// 	0 <= k <= min(nums.length, 25)
//

int maximumLength(int* nums, int numsSize, int k) {
    int count[501] = {0};
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }
    int maxCount = 0;
    for (int i = 0; i < 501; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
        }
    }
    return maxCount + k;        
}
