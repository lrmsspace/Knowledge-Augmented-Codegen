// Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and an integer array queries.
//
// Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
//
// For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
//
// Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
//
// The term gcd(a, b) denotes the greatest common divisor of a and b.
//
// Example:
// Input: nums = [2,3,4], queries = [0,2,2]
//
// Output: [1,2,2]
//
// Explanation:
//
// gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
//
// After sorting in ascending order, gcdPairs = [1, 1, 2].
//
// So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	1 <= nums[i] <= 5 * 104
// 	1 <= queries.length <= 105
// 	0 <= queries[i] < n * (n - 1) / 2
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* gcdValues(int* nums, int numsSize, long long* queries, int queriesSize, int* returnSize) {
    if (!returnSize || numsSize < 2 || queriesSize <= 0) return NULL;

    enum { MAX_NUM = 50000 };
    int freq[MAX_NUM + 1];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    long long gcdCount[MAX_NUM + 1];
    memset(gcdCount, 0, sizeof(gcdCount));
    for (int g = 1; g <= MAX_NUM; ++g) {
        long long count = 0;
        for (int multiple = g; multiple <= MAX_NUM; multiple += g) {
            int f = freq[multiple];
            if (f > 0) {
                count += (long long)f * (f - 1) / 2;
                for (int otherMultiple = multiple + g; otherMultiple <= MAX_NUM; otherMultiple += g) {
                    int of = freq[otherMultiple];
                    if (of > 0) {
                        count += (long long)f * of;
                    }
                }
            }
        }
        gcdCount[g] = count;
    }

    for (int g = 1; g <= MAX_NUM; ++g) {
        gcdCount[g] += gcdCount[g - 1];
    }

    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    for (int i = 0; i < queriesSize; ++i) {
        long long q = queries[i];
        int left = 1, right = MAX_NUM;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (gcdCount[mid] > q) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        results[i] = left;
    }

    *returnSize = queriesSize;
    return results;     
}
