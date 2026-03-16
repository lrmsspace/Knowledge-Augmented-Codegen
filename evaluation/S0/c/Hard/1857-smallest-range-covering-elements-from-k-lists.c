// Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
//
// Problem Description:
// You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
//
// We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
//
// Example:
// Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
// Output: [20,24]
// Explanation: 
// List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
// List 2: [0, 9, 12, 20], 20 is in range [20,24].
// List 3: [5, 18, 22, 30], 22 is in range [20,24].
//
// Constraints:
// nums.length == k
// 	1 <= k <= 3500
// 	1 <= nums[i].length <= 50
// 	-105 <= nums[i][j] <= 105
// 	nums[i] is sorted in non-decreasing order.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 2;
    int totalSize = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSize += numsColSize[i];
    }
    typedef struct {
        int val;
        int listIdx;
        int elemIdx;
    } Element;
    Element *elements = (Element*)malloc(totalSize * sizeof(Element));
    if (!elements) return NULL;
    int idx = 0;
    for (int i = 0; i < numsSize; ++i) {
        for (int j = 0; j < numsColSize[i]; ++j) {
            elements[idx].val = nums[i][j];
            elements[idx].listIdx = i;
            elements[idx].elemIdx = j;
            idx++;
        }
    }
    int cmpElement(const void *a, const void *b) {
        return ((Element*)a)->val - ((Element*)b)->val;
    }
    qsort(elements, totalSize, sizeof(Element), cmpElement);

    int *countPerList = (int*)calloc(numsSize, sizeof(int));
    if (!countPerList) {
        free(elements);
        return NULL;
    }
    int uniqueCount = 0;
    int left = 0, right = 0;
    int bestLeft = elements[0].val, bestRight = elements[1000000].val; // large initial range
    while (right < totalSize) {
        while (right < totalSize && uniqueCount < numsSize) {
            int listIdx = elements[right].listIdx;
            if (countPerList[listIdx] == 0) uniqueCount++;
            countPerList[listIdx]++;
            right++;
        }
        while (uniqueCount == numsSize) {
            if (elements[right - 1].val - elements[left].val < bestRight - bestLeft) {
                bestLeft = elements[left].val;
                bestRight = elements[right - 1].val;
            }
            int listIdx = elements[left].listIdx;
            countPerList[listIdx]--;
            if (countPerList[listIdx] == 0) uniqueCount--;
            left++;
        }
    }

    free(elements);
    free(countPerList);

    int *result = (int*)malloc(2 * sizeof(int));
    result[0] = bestLeft;
    result[1] = bestRight;
    return result;
    
}
