// Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
//
// Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
//
// Example:
// Input: nums = [1,2,0,3,0], k = 1
// Output: 3
// Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
//
// Constraints:
// 1 <= k <= nums.length <= 2000
// 	​​​​​​0 <= nums[i] < 210
//

int minChanges(int* nums, int numsSize, int k) {
    int MAX_XOR = 1 << 10;
    int dp[k + 1][MAX_XOR];
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j < MAX_XOR; ++j) {
            dp[i][j] = numsSize + 1;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < k; ++i) {
        int count[MAX_XOR] = {0};
        int groupSize = 0;
        for (int j = i; j < numsSize; j += k) {
            count[nums[j]]++;
            groupSize++;
        }

        int minPrev = numsSize + 1;
        for (int x = 0; x < MAX_XOR; ++x) {
            if (dp[i][x] < minPrev) {
                minPrev = dp[i][x];
            }
        }

        for (int x = 0; x < MAX_XOR; ++x) {
            dp[i + 1][x] = minPrev + groupSize;
            for (int val = 0; val < MAX_XOR; ++val) {
                int targetXor = x ^ val;
                if (dp[i][targetXor] + (groupSize - count[val]) < dp[i + 1][x]) {
                    dp[i + 1][x] = dp[i][targetXor] + (groupSize - count[val]);
                }
            }
        }
    }

    return dp[k][0];        
}
