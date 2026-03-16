// Source: https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums, an integer k, and an integer multiplier.
//
// You need to perform k operations on nums. In each operation:
//
//
// 	Find the minimum value x in nums. If there are multiple occurrences of the minimum value, select the one that appears first.
// 	Replace the selected minimum value x with x * multiplier.
//
//
// After the k operations, apply modulo 109 + 7 to every value in nums.
//
// Return an integer array denoting the final state of nums after performing all k operations and then applying the modulo.
//
// Example:
// Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
//
// Output: [8,4,6,5,6]
//
// Explanation:
//
//
// 	
// 		
// 			Operation
// 			Result
// 		
// 		
// 			After operation 1
// 			[2, 2, 3, 5, 6]
// 		
// 		
// 			After operation 2
// 			[4, 2, 3, 5, 6]
// 		
// 		
// 			After operation 3
// 			[4, 4, 3, 5, 6]
// 		
// 		
// 			After operation 4
// 			[4, 4, 6, 5, 6]
// 		
// 		
// 			After operation 5
// 			[8, 4, 6, 5, 6]
// 		
// 		
// 			After applying modulo
// 			[8, 4, 6, 5, 6]
//
// Constraints:
// 1 <= nums.length <= 104
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
// 	1 <= multiplier <= 106
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getFinalState(int* nums, int numsSize, int k, int multiplier, int* returnSize) {
    if (!returnSize) return NULL;

    int mod = 1000000007;
    int *result = (int*)malloc(numsSize * sizeof(int));
    if (!result) return NULL;

    // Create a min-heap
    int heapSize = numsSize;
    int *heap = (int*)malloc(heapSize * sizeof(int));
    if (!heap) {
        free(result);
        return NULL;
    }
    for (int i = 0; i < numsSize; ++i) {
        heap[i] = nums[i];
    }

    // Heapify
    for (int i = (heapSize / 2) - 1; i >= 0; --i) {
        int parent = i;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int smallest = parent;

            if (left < heapSize && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < heapSize && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest == parent) break;

            int temp = heap[parent];
            heap[parent] = heap[smallest];
            heap[smallest] = temp;
            parent = smallest;
        }
    }

    // Perform k operations
    for (long long i = 0; i < k; ++i) {
        int minVal = heap[0];
        minVal = (long long)minVal * multiplier % mod;

        // Replace root with new value and heapify down
        heap[0] = minVal;
        int parent = 0;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int smallest = parent;

            if (left < heapSize && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < heapSize && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest == parent) break;

            int temp = heap[parent];
            heap[parent] = heap[smallest];
            heap[smallest] = temp;
            parent = smallest;
        }
    }

    // Copy the final state to result 
    for (int i = 0; i < numsSize; ++i) {
        result[i] = heap[i];
    }
    free(heap);
    *returnSize = numsSize;
    return result;     
}
