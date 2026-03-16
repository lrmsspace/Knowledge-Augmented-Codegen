// Source: https://leetcode.com/problems/binary-subarrays-with-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: nums = [1,0,1,0,1], goal = 2
// Output: 4
// Explanation: The 4 subarrays are bolded and underlined below:
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	nums[i] is either 0 or 1.
// 	0 <= goal <= nums.length
//

int numSubarraysWithSum(int* nums, int numsSize, int goal) {
    int count = 0;
    int prefixSum[numsSize + 1];
    prefixSum[0] = 0;

    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int freq[numsSize + 1];
    for (int i = 0; i <= numsSize; i++) {
        freq[i] = 0;
    }

    for (int i = 0; i <= numsSize; i++) {
        int target = prefixSum[i] - goal;
        if (target >= 0) {
            count += freq[target];
        }
        freq[prefixSum[i]]++;
    }

    return count;       
}
