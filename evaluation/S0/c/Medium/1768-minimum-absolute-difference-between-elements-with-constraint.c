// Source: https://leetcode.com/problems/minimum-absolute-difference-between-elements-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer x.
//
// Find the minimum absolute difference between two elements in the array that are at least x indices apart.
//
// In other words, find two indices i and j such that abs(i - j) >= x and abs(nums[i] - nums[j]) is minimized.
//
// Return an integer denoting the minimum absolute difference between two elements that are at least x indices apart.
//
// Example:
// Input: nums = [4,3,2,4], x = 2
// Output: 0
// Explanation: We can select nums[0] = 4 and nums[3] = 4. 
// They are at least 2 indices apart, and their absolute difference is the minimum, 0. 
// It can be shown that 0 is the optimal answer.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= x < nums.length
//

int minAbsoluteDifference(int* nums, int numsSize, int x) {
    #define MAXN 100005
    #define INF 0x3f3f3f3f

    int bit[MAXN];
    int lowbit(int x) {
        return x & (-x);
    }

    void bit_update(int idx, int val) {
        while (idx < MAXN) {
            if (val < bit[idx]) {
                bit[idx] = val;
            }
            idx += lowbit(idx);
        }
    }

    int bit_query(int idx) {
        int res = INF;
        while (idx > 0) {
            if (bit[idx] < res) {
                res = bit[idx];
            }
            idx -= lowbit(idx);
        }
        return res;
    }

    for (int i = 0; i < MAXN; i++) {
        bit[i] = INF;
    }

    int ans = INF;
    for (int i = x; i < numsSize; i++) {
        int val1 = bit_query(nums[i]);
        if (val1 != INF) {
            int diff1 = val1 - nums[i];
            if (diff1 < 0) {
                diff1 = -diff1;
            }
            if (diff1 < ans) {
                ans = diff1;
            }
        }
        int val2 = bit_query(MAXN - 1) - bit_query(nums[i] - 1);
        if (val2 != INF) {
            int diff2 = val2 - nums[i];
            if (diff2 < 0) {
                diff2 = -diff2;
            }
            if (diff2 < ans) {
                ans = diff2;
            }
        }
        bit_update(nums[i - x], nums[i - x]);
    }
    return ans;     
}
