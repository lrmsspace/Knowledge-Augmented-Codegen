// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 30
//

int squareFreeSubsets(int* nums, int numsSize) {
    int mod = 1e9 + 7;
    int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int freq[31];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    long long dp[1 << 10];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int num = 2; num <= 30; num++) {
        if (freq[num] == 0) {
            continue;
        }

        int subsetMask = 0;
        bool isSquareFree = true;
        for (int j = 0; j < 10; j++) {
            int primeNum = prime[j];
            int count = 0;
            int temp = num;
            while (temp % primeNum == 0) {
                temp /= primeNum;
                count++;
            }
            if (count > 1) {
                isSquareFree = false;
                break;
            }
            if (count == 1) {
                subsetMask |= (1 << j);
            }
        }
        if (!isSquareFree) {
            continue;
        }

        for (int mask = (1 << 10) - 1; mask >= 0; mask--) {
            if ((mask & subsetMask) == 0) {
                dp[mask | subsetMask] = (dp[mask | subsetMask] + dp[mask] * freq[num]) % mod;
            }
        }
    }

    long long result = 0;
    for (int mask = 1; mask < (1 << 10); mask++) {
        result = (result + dp[mask]) % mod;
    }

    if (freq[1] > 0) {
        long long pow2 = 1;
        for (int i = 0; i < freq[1]; i++) {
            pow2 = (pow2 * 2) % mod;
        }
        result = (result * pow2) % mod;
    }

    return (int)result;     
}
