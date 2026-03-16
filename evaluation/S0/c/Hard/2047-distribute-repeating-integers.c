// Source: https://leetcode.com/problems/distribute-repeating-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
//
//
// 	The ith customer gets exactly quantity[i] integers,
// 	The integers the ith customer gets are all equal, and
// 	Every customer is satisfied.
//
//
// Return true if it is possible to distribute nums according to the above conditions.
//
// Example:
// Input: nums = [1,2,3,4], quantity = [2]
// Output: false
// Explanation: The 0th customer cannot be given two different integers.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= 1000
// 	m == quantity.length
// 	1 <= m <= 10
// 	1 <= quantity[i] <= 105
// 	There are at most 50 unique values in nums.
//

bool canDistribute(int* nums, int numsSize, int* quantity, int quantitySize) {
    int freq[50] = {0};
    int uniqueCount = 0;
    int counts[51] = {0}; // counts[i]: number of unique integers with frequency i

    // Count frequencies of each unique integer
    for (int i = 0; i < numsSize; ++i) {
        int found = 0;
        for (int j = 0; j < uniqueCount; ++j) {
            if (freq[j] > 0 && nums[i] == nums[j]) {
                freq[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq[uniqueCount++] = nums[i];
            freq[uniqueCount - 1] = 1;
        }
    }

    // Count how many unique integers have each frequency
    for (int i = 0; i < uniqueCount; ++i) {
        counts[freq[i]]++;
    }

    // Dynamic programming to check if we can satisfy all quantities
    int dp[1 << quantitySize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int f = 1; f <= numsSize; ++f) {
        if (counts[f] == 0) continue;

        for (int k = 0; k < counts[f]; ++k) {
            for (int mask = (1 << quantitySize) - 1; mask >= 0; --mask) {
                if (!dp[mask]) continue;

                for (int submask = mask; submask; submask = (submask - 1) & mask) {
                    int sum = 0;
                    for (int i = 0; i < quantitySize; ++i) {
                        if (submask & (1 << i)) {
                            sum += quantity[i];
                        }
                    }
                    if (sum <= f) {
                        dp[mask] = 1;
                    }
                }
            }
        }
    }

    return dp[(1 << quantitySize) - 1];     
}
