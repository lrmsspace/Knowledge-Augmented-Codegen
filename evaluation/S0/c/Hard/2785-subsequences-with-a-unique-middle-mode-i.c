// Source: https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, find the number of subsequences of size 5 of nums with a unique middle mode.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A mode of a sequence of numbers is defined as the element that appears the maximum number of times in the sequence.
//
// A sequence of numbers contains a unique mode if it has only one mode.
//
// A sequence of numbers seq of size 5 contains a unique middle mode if the middle element (seq[2]) is a unique mode.
//
// Example:
// Input: nums = [1,1,1,1,1,1]
//
// Output: 6
//
// Explanation:
//
// [1, 1, 1, 1, 1] is the only subsequence of size 5 that can be formed, and it has a unique middle mode of 1. This subsequence can be formed in 6 different ways, so the output is 6.
//
// Constraints:
// 5 <= nums.length <= 1000
//  -109 <= nums[i] <= 109
//

int subsequencesWithMiddleMode(int* nums, int numsSize) {
    const int MOD = 1000000007;
    long long result = 0;

    for (int mid = 0; mid < numsSize; mid++) {
        int leftCount[2010] = {0};
        int rightCount[2010] = {0};

        for (int i = 0; i < mid; i++) {
            if (nums[i] < nums[mid]) {
                leftCount[nums[i] + 1000]++;
            }
        }

        for (int j = mid + 1; j < numsSize; j++) {
            if (nums[j] < nums[mid]) {
                rightCount[nums[j] + 1000]++;
            }
        }

        for (int val = -1000; val <= 1000; val++) {
            int idx = val + 1000;
            if (leftCount[idx] > 0 && rightCount[idx] > 0) {
                result = (result + (long long)leftCount[idx] * rightCount[idx]) % MOD;
            }
        }
    }

    return (int)result;     
}
