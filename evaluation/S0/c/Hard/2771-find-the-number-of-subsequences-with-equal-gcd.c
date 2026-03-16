// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
//
//
// 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
//
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 10
//
// Explanation:
//
// The subsequence pairs which have the GCD of their elements equal to 1 are:
//
//
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 200
//

int subsequencePairCount(int* nums, int numsSize) {
    const int MOD = 1000000007;
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }

    int *count = (int*)calloc(maxNum + 1, sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        count[nums[i]]++;
    }

    int *dp = (int*)calloc(maxNum + 1, sizeof(int));
    for (int g = maxNum; g >= 1; --g) {
        int total = 0;
        for (int multiple = g; multiple <= maxNum; multiple += g) {
            total += count[multiple];
        }
        if (total == 0) {
            dp[g] = 0;
            continue;
        }
        long long subseqCount = (1LL << total) - 1; // 2^total - 1
        for (int multiple = 2 * g; multiple <= maxNum; multiple += g) {
            subseqCount = (subseqCount - dp[multiple] + MOD) % MOD;
        }
        dp[g] = (int)subseqCount;
    }

    long long result = 0;
    for (int g = 1; g <= maxNum; ++g) {
        result = (result + ((long long)dp[g] * dp[g]) % MOD) % MOD;
    }

    free(count);
    free(dp);
    return (int)result;     
}
