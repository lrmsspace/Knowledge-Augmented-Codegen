// Source: https://leetcode.com/problems/the-number-of-good-subsets/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. We call a subset of nums good if its product can be represented as a product of one or more distinct prime numbers.
//
//
// 	For example, if nums = [1, 2, 3, 4]:
//
// 	
// 		[2, 3], [1, 2, 3], and [1, 3] are good subsets with products 6 = 2*3, 6 = 2*3, and 3 = 3 respectively.
// 		[1, 4] and [4] are not good subsets with products 4 = 2*2 and 4 = 2*2 respectively.
// 	
// 	
//
//
// Return the number of different good subsets in nums modulo 109 + 7.
//
// A subset of nums is any array that can be obtained by deleting some (possibly none or all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 6
// Explanation: The good subsets are:
// - [1,2]: product is 2, which is the product of distinct prime 2.
// - [1,2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [1,3]: product is 3, which is the product of distinct prime 3.
// - [2]: product is 2, which is the product of distinct prime 2.
// - [2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [3]: product is 3, which is the product of distinct prime 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 30
//

int numberOfGoodSubsets(int* nums, int numsSize) {
    const int MOD = 1000000007;
    const int primes[] = {2,3,5,7,11,13,17,19,23,29};
    const int primeCount = sizeof(primes) / sizeof(primes[0]);
    int freq[31];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    /* Precompute valid masks for numbers 2 to 30 */
    int masks[31];
    memset(masks, 0, sizeof(masks));
    for (int num = 2; num <= 30; ++num) {
        int mask = 0;
        int x = num;
        int isValid = 1;
        for (int j = 0; j < primeCount; ++j) {
            int prime = primes[j];
            int count = 0;
            while (x % prime == 0) {
                x /= prime;
                count++;
            }
            if (count > 1) {
                isValid = 0; /* has squared prime factor */
                break;
            }
            if (count == 1) {
                mask |= (1 << j);
            }
        }
        if (isValid && x == 1) {
            masks[num] = mask;
        } else {
            masks[num] = -1; /* invalid number */
        }
    }

    /* DP array */
    int dp[1 << primeCount];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; /* empty subset */

    for (int num = 2; num <= 30; ++num) {
        if (masks[num] == -1 || freq[num] == 0) continue;
        int currMask = masks[num];
        int count = freq[num];

        for (int mask = (1 << primeCount) - 1; mask >= 0; --mask) {
            if ((mask & currMask) == 0) { /* no overlapping primes */
                int newMask = mask | currMask;
                dp[newMask] = (dp[newMask] + (long long)dp[mask] * count) % MOD;
            }
        }
    }

    /* Sum all dp values except the empty subset */
    long long result = 0;
    for (int mask = 1; mask < (1 << primeCount); ++mask) {
        result = (result + dp[mask]) % MOD;
    }
    /* Account for the number of 1's */
    if (freq[1] > 0) {
        long long pow2 = 1;
        for (int i = 0; i < freq[1]; ++i) {
            pow2 = (pow2 * 2) % MOD;
        }
        result = (result * pow2) % MOD;
    }
    return (int)result;
}
