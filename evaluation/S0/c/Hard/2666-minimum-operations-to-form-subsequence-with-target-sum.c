// Source: https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of non-negative powers of 2, and an integer target.
//
// In one operation, you must apply the following changes to the array:
//
//
// 	Choose any element of the array nums[i] such that nums[i] > 1.
// 	Remove nums[i] from the array.
// 	Add two occurrences of nums[i] / 2 to the end of nums.
//
//
// Return the minimum number of operations you need to perform so that nums contains a subsequence whose elements sum to target. If it is impossible to obtain such a subsequence, return -1.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [1,2,8], target = 7
// Output: 1
// Explanation: In the first operation, we choose element nums[2]. The array becomes equal to nums = [1,2,4,4].
// At this stage, nums contains the subsequence [1,2,4] which sums up to 7.
// It can be shown that there is no shorter sequence of operations that results in a subsequnce that sums up to 7.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 230
// 	nums consists only of non-negative powers of two.
// 	1 <= target < 231
//

int minOperations(int* nums, int numsSize, int target) {
    int count[31] = {0};
    long long sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        int bit = 0;
        while ((1 << bit) < nums[i]) bit++;
        count[bit]++;
    }
    if (sum < target) return -1;

    int operations = 0;
    for (int bit = 0; bit < 31; bit++) {
        if (target & (1 << bit)) {
            if (count[bit] > 0) {
                count[bit]--;
            } else {
                int nextBit = bit + 1;
                while (nextBit < 31 && count[nextBit] == 0) nextBit++;
                if (nextBit == 31) return -1; // Should not happen due to earlier sum check
                // Split the next available power of two
                for (int b = nextBit; b > bit; b--) {
                    count[b]--;
                    count[b - 1] += 2;
                    operations++;
                }
                count[bit]--; // Use one of the split parts
            }
        }
        // Combine leftover parts to form higher powers of two
        if (bit < 30) {
            count[bit + 1] += count[bit] / 2;
        }
    }
    return operations;      
}
