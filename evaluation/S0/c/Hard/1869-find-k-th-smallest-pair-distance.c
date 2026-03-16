// Source: https://leetcode.com/problems/find-k-th-smallest-pair-distance/   |   Difficulty: Hard
//
// Problem Description:
// The distance of a pair of integers a and b is defined as the absolute difference between a and b.
//
// Given an integer array nums and an integer k, return the kth smallest distance among all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.
//
// Example:
// Input: nums = [1,3,1], k = 1
// Output: 0
// Explanation: Here are all the pairs:
// (1,3) -> 2
// (1,1) -> 0
// (3,1) -> 2
// Then the 1st smallest distance pair is (1,1), and its distance is 0.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 104
// 	0 <= nums[i] <= 106
// 	1 <= k <= n * (n - 1) / 2
//

int smallestDistancePair(int* nums, int numsSize, int k) {
    /* Counting sort to get frequency of each number */
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }
    int *count = (int*)calloc(maxNum + 1, sizeof(int));
    if (!count) return -1; /* allocation failure */
    for (int i = 0; i < numsSize; ++i) {
        count[nums[i]]++;
    }

    /* Binary search for the k-th smallest distance */
    int left = 0, right = maxNum;
    while (left < right) {
        int mid = left + (right - left) / 2;
        /* Count pairs with distance <= mid */
        long long pairCount = 0;
        int j = 0;
        for (int i = 0; i <= maxNum; ++i) {
            if (count[i] == 0) continue;
            while (j <= maxNum && j - i <= mid) {
                j++;
            }
            for (int x = i + 1; x < j; ++x) {
                if (count[x] > 0) {
                    pairCount += (long long)count[i] * count[x];
                }
            }
            /* Count pairs within the same number */
            if (mid >= 0 && count[i] > 1) {
                pairCount += (long long)count[i] * (count[i] - 1) / 2;
            }
        }

        if (pairCount >= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    free(count);
    return left;        
}
