// Source: https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. A sequence of integers seq is called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].
//
// Return the maximum possible length of a good subsequence of nums.
//
// Example:
// Input: nums = [1,2,1,1,3], k = 2
//
// Output: 4
//
// Explanation:
//
// The maximum length subsequence is [1,2,1,1,3].
//
// Constraints:
// 1 <= nums.length <= 5 * 103
// 	1 <= nums[i] <= 109
// 	0 <= k <= min(50, nums.length)
//

int maximumLength(int* nums, int numsSize, int k) {
    int count[2 * 5000 + 1] = {0}; /* offset by 5000 to handle negative indices */
    count[5000] = 0; /* base case: zero changes */

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        int newCount[2 * 5000 + 1];
        memcpy(newCount, count, sizeof(count));

        for (int changes = -5000; changes <= 5000; ++changes) {
            if (count[changes + 5000] == 0 && changes != 0) continue;

            /* Option 1: Include nums[i] without change */
            newCount[changes + 5000] = 
                (newCount[changes + 5000] > count[changes + 5000] + 1) ?
                newCount[changes + 5000] : count[changes + 5000] + 1;

            /* Option 2: Include nums[i] with change (if we have changes left) */
            if (changes + 1 <= k) {
                newCount[changes + 1 + 5000] = 
                    (newCount[changes + 1 + 5000] > count[changes + 5000] + 1) ?
                    newCount[changes + 1 + 5000] : count[changes + 5000] + 1;
            }
        }
        memcpy(count, newCount, sizeof(count));
    }

    int maxLength = 0;
    for (int changes = 0; changes <= k; ++changes) {
        if (count[changes + 5000] > maxLength) {
            maxLength = count[changes + 5000];
        }
    }
    return maxLength;       
}
