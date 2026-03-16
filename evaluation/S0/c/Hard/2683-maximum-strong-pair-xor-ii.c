// Source: https://leetcode.com/problems/maximum-strong-pair-xor-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums. A pair of integers x and y is called a strong pair if it satisfies the condition:
//
//
// 	|x - y| <= min(x, y)
//
//
// You need to select two integers from nums such that they form a strong pair and their bitwise XOR is the maximum among all strong pairs in the array.
//
// Return the maximum XOR value out of all possible strong pairs in the array nums.
//
// Note that you can pick the same integer twice to form a pair.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: 7
// Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2), (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
// The maximum XOR possible from these pairs is 3 XOR 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 220 - 1
//

int maximumStrongPairXor(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    /* sort nums */
    qsort(nums, numsSize, sizeof(int), (int(*)(const void*, const void*))strcmp);

    int maxXor = 0;
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i; j < numsSize; ++j) {
            if (nums[j] - nums[i] <= nums[i]) {
                int xorVal = nums[i] ^ nums[j];
                if (xorVal > maxXor) maxXor = xorVal;
            } else {
                break; /* further j will only increase the difference */
            }
        }
    }

    return maxXor;      
}
