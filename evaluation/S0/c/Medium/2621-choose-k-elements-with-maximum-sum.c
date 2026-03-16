// Source: https://leetcode.com/problems/choose-k-elements-with-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.
//
// For each index i from 0 to n - 1, perform the following:
//
//
// 	Find all indices j where nums1[j] is less than nums1[i].
// 	Choose at most k values of nums2[j] at these indices to maximize the total sum.
//
//
// Return an array answer of size n, where answer[i] represents the result for the corresponding index i.
//
// Example:
// Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2
//
// Output: [80,30,0,80,50]
//
// Explanation:
//
//
// 	For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
// 	For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
// 	For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
// 	For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
// 	For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 106
// 	1 <= k <= n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* findMaxSum(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize) {
    typedef struct {
        int num1;
        int num2;
    } Pair;

    int compare(const void* a, const void* b) {
        return ((Pair*)a)->num1 - ((Pair*)b)->num1;
    }

    Pair* pairs = (Pair*)malloc(nums1Size * sizeof(Pair));
    for (int i = 0; i < nums1Size; i++) {
        pairs[i].num1 = nums1[i];
        pairs[i].num2 = nums2[i];
    }

    qsort(pairs, nums1Size, sizeof(Pair), compare);

    long long* result = (long long*)calloc(nums1Size, sizeof(long long));
    long long currentSum = 0;
    int* minHeap = (int*)malloc(k * sizeof(int));
    int heapSize = 0;

    for (int i = 0, j = 0; i < nums1Size; i++) {
        while (j < nums1Size && pairs[j].num1 < pairs[i].num1) {
            if (heapSize < k) {
                minHeap[heapSize++] = pairs[j].num2;
                currentSum += pairs[j].num2;
                if (heapSize == k) {
                    for (int m = heapSize / 2 - 1; m >= 0; m--) {
                        heapify(minHeap, heapSize, m);
                    }
                }
            } else if (heapSize == k && pairs[j].num2 > minHeap[0]) {
                currentSum += pairs[j].num2 - minHeap[0];
                minHeap[0] = pairs[j].num2;
                heapify(minHeap, heapSize, 0);
            }
            j++;
        }
        result[i] = currentSum;
    }

    free(pairs);
    free(minHeap);
    *returnSize = nums1Size;
    return result;      
}
