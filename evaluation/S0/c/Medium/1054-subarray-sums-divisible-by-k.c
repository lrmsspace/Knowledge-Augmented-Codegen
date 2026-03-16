// Source: https://leetcode.com/problems/subarray-sums-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [4,5,0,-2,-3,1], k = 5
// Output: 7
// Explanation: There are 7 subarrays with a sum divisible by k = 5:
// [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	-104 <= nums[i] <= 104
// 	2 <= k <= 104
//

int subarraysDivByK(int* nums, int numsSize, int k) {
    int count = 0;
    int prefixSum = 0;
    int modCount[k];
    for (int i = 0; i < k; i++) {
        modCount[i] = 0;
    }
    modCount[0] = 1; // There's one way to have a sum of 0 (the empty subarray)

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        int mod = prefixSum % k;
        if (mod < 0) {
            mod += k; // Adjust for negative mods
        }
        count += modCount[mod];
        modCount[mod]++;
    }

    return count;       
}
