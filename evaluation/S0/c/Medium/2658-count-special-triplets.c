// Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// A special triplet is defined as a triplet of indices (i, j, k) such that:
//
//
// 	0 <= i < j < k < n, where n = nums.length
// 	nums[i] == nums[j] * 2
// 	nums[k] == nums[j] * 2
//
//
// Return the total number of special triplets in the array.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [6,3,6]
//
// Output: 1
//
// Explanation:
//
// The only special triplet is (i, j, k) = (0, 1, 2), where:
//
//
// 	nums[0] = 6, nums[1] = 3, nums[2] = 6
// 	nums[0] = nums[1] * 2 = 3 * 2 = 6
// 	nums[2] = nums[1] * 2 = 3 * 2 = 6
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//

int specialTriplets(int* nums, int numsSize) {
    const int MOD = 1e9 + 7;
    int maxVal = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    int freqSize = maxVal + 1;
    int* freqLeft = (int*)calloc(freqSize, sizeof(int));
    int* freqRight = (int*)calloc(freqSize, sizeof(int));

    for (int i = 0; i < numsSize; ++i) {
        freqRight[nums[i]]++;
    }

    long long result = 0;

    for (int j = 0; j < numsSize; ++j) {
        freqRight[nums[j]]--;

        int valJ = nums[j];
        int valI = valJ * 2;
        int valK = valJ * 2;

        long long countI = (valI <= maxVal) ? freqLeft[valI] : 0;
        long long countK = (valK <= maxVal) ? freqRight[valK] : 0;

        result = (result + countI * countK) % MOD;

        freqLeft[nums[j]]++;
    }

    free(freqLeft);
    free(freqRight);

    return (int)result;     
}
