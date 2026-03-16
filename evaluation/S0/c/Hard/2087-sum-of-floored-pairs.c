// Source: https://leetcode.com/problems/sum-of-floored-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be too large, return it modulo 109 + 7.
//
// The floor() function returns the integer part of the division.
//
// Example:
// Input: nums = [2,5,9]
// Output: 10
// Explanation:
// floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
// floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
// floor(5 / 2) = 2
// floor(9 / 2) = 4
// floor(9 / 5) = 1
// We calculate the floor of the division for every pair of indices in the array then sum them up.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

int sumOfFlooredPairs(int* nums, int numsSize) {
    const int MOD = 1000000007;
    const int MAX_VAL = 100000;

    int freq[MAX_VAL + 1];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    int prefixFreq[MAX_VAL + 1];
    memset(prefixFreq, 0, sizeof(prefixFreq));
    for (int i = 1; i <= MAX_VAL; ++i) {
        prefixFreq[i] = prefixFreq[i - 1] + freq[i];
    }

    long long result = 0;
    for (int i = 1; i <= MAX_VAL; ++i) {
        if (freq[i] == 0) continue;
        for (int k = 1; k * i <= MAX_VAL; ++k) {
            int left = k * i;
            int right = (k + 1) * i - 1;
            if (right > MAX_VAL) right = MAX_VAL;
            int countInRange = prefixFreq[right] - prefixFreq[left - 1];
            result = (result + (long long)freq[i] * countInRange * k) % MOD;
        }
    }

    return (int)result;     
}
