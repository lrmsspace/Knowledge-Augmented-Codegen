// Source: https://leetcode.com/problems/top-k-frequent-elements/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
//
// Example:
// Input: nums = [1,1,1,2,2,3], k = 2
//
// Output: [1,2]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	k is in the range [1, the number of unique elements in the array].
// 	It is guaranteed that the answer is unique.
//
//
//  
// Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    // Frequency map
    int freqMap[20001] = {0};
    for (int i = 0; i < numsSize; i++) {
        freqMap[nums[i] + 10000]++;
    }

    // Bucket sort based on frequency
    int** buckets = (int**)calloc(numsSize + 1, sizeof(int*));
    int* bucketSizes = (int*)calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i < 20001; i++) {
        int freq = freqMap[i];
        if (freq > 0) {
            if (buckets[freq] == NULL) {
                buckets[freq] = (int*)malloc(numsSize * sizeof(int));
            }
            buckets[freq][bucketSizes[freq]++] = i - 10000;
        }
    }

    // Collect top k frequent elements
    int* result = (int*)malloc(k * sizeof(int));
    int count = 0;
    for (int i = numsSize; i >= 0 && count < k; i--) {
        if (buckets[i] != NULL) {
            for (int j = 0; j < bucketSizes[i] && count < k; j++) {
                result[count++] = buckets[i][j];
            }
        }
    }

    // Free allocated memory for buckets
    for (int i = 0; i <= numsSize; i++) {
        if (buckets[i] != NULL) {
            free(buckets[i]);
        }
    }
    free(buckets);
    free(bucketSizes);

    *returnSize = k;
    return result;      
}
