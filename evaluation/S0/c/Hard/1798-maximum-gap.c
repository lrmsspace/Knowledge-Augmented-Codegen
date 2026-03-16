// Source: https://leetcode.com/problems/maximum-gap/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.
//
// You must write an algorithm that runs in linear time and uses linear extra space.
//
// Example:
// Input: nums = [3,6,9,1]
// Output: 3
// Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

int maximumGap(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    int minVal = nums[0], maxVal = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < minVal) minVal = nums[i];
        if (nums[i] > maxVal) maxVal = nums[i];
    }

    int bucketSize = (maxVal - minVal) / (numsSize - 1);
    if (bucketSize == 0) bucketSize = 1;
    int bucketCount = (maxVal - minVal) / bucketSize + 1;

    int* bucketMin = (int*)malloc(bucketCount * sizeof(int));
    int* bucketMax = (int*)malloc(bucketCount * sizeof(int));
    int* bucketUsed = (int*)calloc(bucketCount, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int idx = (nums[i] - minVal) / bucketSize;
        if (!bucketUsed[idx]) {
            bucketMin[idx] = nums[i];
            bucketMax[idx] = nums[i];
            bucketUsed[idx] = 1;
        } else {
            if (nums[i] < bucketMin[idx]) bucketMin[idx] = nums[i];
            if (nums[i] > bucketMax[idx]) bucketMax[idx] = nums[i];
        }
    }

    int maxGap = 0;
    int prevMax = minVal;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketUsed[i]) {
            if (bucketMin[i] - prevMax > maxGap) {
                maxGap = bucketMin[i] - prevMax;
            }
            prevMax = bucketMax[i];
        }
    }

    free(bucketMin);
    free(bucketMax);
    free(bucketUsed);

    return maxGap;
            
}
