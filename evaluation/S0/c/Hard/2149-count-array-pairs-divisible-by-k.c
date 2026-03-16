// Source: https://leetcode.com/problems/count-array-pairs-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// Given a 0-indexed integer array nums of length n and an integer k, return the number of pairs (i, j) such that:
//
//
// 	0 <= i < j <= n - 1 and
// 	nums[i] * nums[j] is divisible by k.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 2
// Output: 7
// Explanation: 
// The 7 pairs of indices whose corresponding products are divisible by 2 are
// (0, 1), (0, 3), (1, 2), (1, 3), (1, 4), (2, 3), and (3, 4).
// Their products are 2, 4, 6, 8, 10, 12, and 20 respectively.
// Other pairs such as (0, 2) and (2, 4) have products 3 and 15 respectively, which are not divisible by 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 105
//

long long countPairs(int* nums, int numsSize, int k) {
    if (!nums || numsSize <= 1 || k <= 0) return 0;

    int freq[100001] = {0};
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    long long result = 0;
    for (int i = 1; i <= 100000; ++i) {
        if (freq[i] == 0) continue;
        for (int j = i; j <= 100000; j += i) {
            if (freq[j] == 0) continue;
            if ((long long)i * j % k == 0) {
                if (i == j) {
                    result += (long long)freq[i] * (freq[i] - 1) / 2;
                } else {
                    result += (long long)freq[i] * freq[j];
                }
            }
        }
    }

    return result;      
}
