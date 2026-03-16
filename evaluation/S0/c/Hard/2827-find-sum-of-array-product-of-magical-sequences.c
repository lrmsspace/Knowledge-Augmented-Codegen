// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, m and k, and an integer array nums.
// A sequence of integers seq is called magical if:
//
//
// 	seq has a size of m.
// 	0 <= seq[i] < nums.length
// 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
//
//
// The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
//
// Return the sum of the array products for all valid magical sequences.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A set bit refers to a bit in the binary representation of a number that has a value of 1.
//
// Example:
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
//
// Output: 991600007
//
// Explanation:
//
// All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
//
// Constraints:
// 1 <= k <= m <= 30
// 	1 <= nums.length <= 50
// 	1 <= nums[i] <= 108
//

int magicalSum(int m, int k, int* nums, int numsSize) {
    const int MOD = 1000000007;

    /* Precompute nCr using Pascal's triangle */
    int nCr[31][31];
    memset(nCr, 0, sizeof(nCr));
    for (int n = 0; n <= 30; ++n) {
        nCr[n][0] = 1;
        for (int r = 1; r <= n; ++r) {
            nCr[n][r] = (nCr[n - 1][r - 1] + nCr[n - 1][r]) % MOD;
        }
    }

    /* Precompute sum of nums^i for i = 0 to m */
    long long sumPows[31];
    sumPows[0] = numsSize % MOD;
    for (int i = 1; i <= m; ++i) {
        long long sum = 0;
        for (int j = 0; j < numsSize; ++j) {
            long long powVal = 1;
            for (int p = 0; p < i; ++p) {
                powVal = (powVal * nums[j]) % MOD;
            }
            sum = (sum + powVal) % MOD;
        }
        sumPows[i] = sum;
    }

    /* Calculate the final answer */
    long long result = 0;
    for (int bits = 0; bits <= m; ++bits) {
        if (__builtin_popcount(bits) == k) {
            int ones = bits;
            int zeros = m - bits;
            long long ways = (long long)nCr[m][ones] * sumPows[ones] % MOD * sumPows[zeros] % MOD;
            result = (result + ways) % MOD;
        }
    }

    return (int)result;     
}
