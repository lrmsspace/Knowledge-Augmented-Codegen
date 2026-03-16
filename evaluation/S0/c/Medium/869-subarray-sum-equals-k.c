// Source: https://leetcode.com/problems/subarray-sum-equals-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1], k = 2
// Output: 2
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-1000 <= nums[i] <= 1000
// 	-107 <= k <= 107
//

int subarraySum(int* nums, int numsSize, int k) {
    int count = 0;
    int prefixSum = 0;
    // Hash map to store the frequency of prefix sums
    // Key: prefix sum, Value: frequency
    #define HASH_SIZE 40001
    int hashMap[HASH_SIZE] = {0};
    hashMap[20000] = 1; // To handle prefix sum equal to k

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        int target = prefixSum - k;
        if (target + 20000 >= 0 && target + 20000 < HASH_SIZE) {
            count += hashMap[target + 20000];
        }
        if (prefixSum + 20000 >= 0 && prefixSum + 20000 < HASH_SIZE) {
            hashMap[prefixSum + 20000]++;
        }
    }

    return count;       
}
