// Source: https://leetcode.com/problems/count-the-number-of-good-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// A partition of an array into one or more contiguous subarrays is called good if no two subarrays contain the same number.
//
// Return the total number of good partitions of nums.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 8
// Explanation: The 8 possible good partitions are: ([1], [2], [3], [4]), ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2], [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]), and ([1,2,3,4]).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

int numberOfGoodPartitions(int* nums, int numsSize) {
    if (!nums || numsSize <= 0) return 0;

    const int MOD = 1000000007;
    int totalWays = 1; /* start with one way to partition an empty array */
    int currentWays = 1; /* ways to partition up to the previous element */
    /* Use a hash set to track seen numbers in the current partition */
    #define HASH_SIZE 131071
    int *hashSet = (int*)calloc(HASH_SIZE, sizeof(int));
    if (!hashSet) return 0;

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        int hashIndex = (num % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
        /* Check if num is already in the current partition */
        if (hashSet[hashIndex] == 1) {
            /* Start a new partition */
            totalWays = (totalWays + currentWays) % MOD;
            currentWays = totalWays;
            /* Reset hash set for new partition */
            memset(hashSet, 0, HASH_SIZE * sizeof(int));
        }
        /* Add num to the current partition */
        hashSet[hashIndex] = 1;
    }

    free(hashSet);
    return totalWays % MOD;     
}
