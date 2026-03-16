// Source: https://leetcode.com/problems/sliding-window-median/   |   Difficulty: Hard
//
// Problem Description:
// The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
//
//
// 	For examples, if arr = [2,3,4], the median is 3.
// 	For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
//
//
// You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
// Explanation: 
// Window position                Median
// ---------------                -----
// [1  3  -1] -3  5  3  6  7        1
//  1 [3  -1  -3] 5  3  6  7       -1
//  1  3 [-1  -3  5] 3  6  7       -1
//  1  3  -1 [-3  5  3] 6  7        3
//  1  3  -1  -3 [5  3  6] 7        5
//  1  3  -1  -3  5 [3  6  7]       6
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    // Implementation of sliding window median using two heaps (max-heap and min-heap)
    
    #define MAX_HEAP_SIZE 100000

    typedef struct {
        int* data;
        int size;
        int capacity;
    } Heap;

    Heap* createHeap(int capacity) {
        Heap* heap = (Heap*)malloc(sizeof(Heap));
        heap->data = (int*)malloc(sizeof(int) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void maxHeapifyUp(Heap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[index] > heap->data[parent]) {
                swap(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void minHeapifyUp(Heap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[index] < heap->data[parent]) {
                swap(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void maxHeapifyDown(Heap* heap, int index) {
        while (index < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < heap->size && heap->data[left] > heap->data[largest]) {
                largest = left;
            }
            if (right < heap->size && heap->data[right] > heap->data[largest]) {
                largest = right;
            }
            if (largest != index) {
                swap(&heap->data[index], &heap->data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    void minHeapifyDown(Heap* heap, int index) {
        while (index < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < heap->size && heap->data[left] < heap->data[smallest]) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right] < heap->data[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                swap(&heap->data[index], &heap->data[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    void maxHeapInsert(Heap* heap, int value) {
        heap->data[heap->size] = value;
        heap->size++;
        maxHeapifyUp(heap, heap->size - 1);
    }
    void minHeapInsert(Heap* heap, int value) {
        heap->data[heap->size] = value;
        heap->size++;
        minHeapifyUp(heap, heap->size - 1);
    }
    int maxHeapExtract(Heap* heap) {
        int root = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        maxHeapifyDown(heap, 0);
        return root;
    }
    int minHeapExtract(Heap* heap) {
        int root = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        minHeapifyDown(heap, 0);
        return root;
    }
    double* result = (double*)malloc(sizeof(double) * (numsSize - k + 1));
    *returnSize = numsSize - k + 1;
    Heap* maxHeap = createHeap(MAX_HEAP_SIZE);
    Heap* minHeap = createHeap(MAX_HEAP_SIZE);
    for (int i = 0; i < numsSize; i++) {
        if (maxHeap->size == 0 || nums[i] <= maxHeap->data[0]) {
            maxHeapInsert(maxHeap, nums[i]);
        } else {
            minHeapInsert(minHeap, nums[i]);
        }

        // Balance heaps
        if (maxHeap->size > minHeap->size + 1) {
            int val = maxHeapExtract(maxHeap);
            minHeapInsert(minHeap, val);
        } else if (minHeap->size > maxHeap->size) {
            int val = minHeapExtract(minHeap);
            maxHeapInsert(maxHeap, val);
        }

        if (i >= k - 1) {
            // Calculate median
            if (k % 2 == 0) {
                result[i - k + 1] = ((double)maxHeap->data[0] + (double)minHeap->data[0]) / 2.0;
            } else {
                result[i - k + 1] = (double)maxHeap->data[0];
            }

            // Remove the element going out of the window
            int toRemove = nums[i - k + 1];
            if (toRemove <= maxHeap->data[0]) {
                // Remove from maxHeap
                // Simple approach: rebuild heaps
                Heap* newMaxHeap = createHeap(MAX_HEAP_SIZE);
                Heap* newMinHeap = createHeap(MAX_HEAP_SIZE);
                for (int j = 0; j < maxHeap->size; j++) {
                    if (maxHeap->data[j] != toRemove) {
                        maxHeapInsert(newMaxHeap, maxHeap->data[j]);
                    }
                }
                for (int j = 0; j < minHeap->size; j++) {
                    maxHeapInsert(newMinHeap, minHeap->data[j]);
                }
                free(maxHeap->data);
                free(minHeap->data);
                free(maxHeap);
                free(minHeap);
                maxHeap = newMaxHeap;
                minHeap = newMinHeap;
            } else {
                // Remove from minHeap
                Heap* newMaxHeap = createHeap(MAX_HEAP_SIZE);
                Heap* newMinHeap = createHeap(MAX_HEAP_SIZE);
                for (int j = 0; j < minHeap->size; j++) {
                    if (minHeap->data[j] != toRemove) {
                        minHeapInsert(newMinHeap, minHeap->data[j]);
                    }
                for (int j = 0; j < maxHeap->size; j++) {
                    maxHeapInsert(newMaxHeap, maxHeap->data[j]);
                }
                free(maxHeap->data);
                free(minHeap->data);
                free(maxHeap);
                free(minHeap);
                maxHeap = newMaxHeap;
                minHeap = newMinHeap;
            }
            // Balance heaps again
            if (maxHeap->size > minHeap->size + 1) {
                int val = maxHeapExtract(maxHeap);
                minHeapInsert(minHeap, val);
            } else if (minHeap->size > maxHeap->size) {
                int val = minHeapExtract(minHeap);
                maxHeapInsert(maxHeap, val);
            }
        }
            result[*returnSize] = (char*)malloc(sizeof(char) * (k + 1));
            int pathIdx = *returnSize;
            (*returnSize)++;
            void backtrack(int node, int depth) {
                if (node == 0) {
                    result[pathIdx][depth] = '\0';
                    return;
                }
                for (int i = 0; i < parentCnt[node]; i++) {
                    int parent = parents[node][i];
                    result[pathIdx][depth] = words[node - 1][0]; // First char of the word
                    backtrack(parent, depth - 1);
                }
            }
            backtrack(endIdx, dist[endIdx]);
        }
    }

    // Cleanup
    for (int i = 0; i < wordsSize + 1; i++) {
        free(adj[i]);
        free(parents[i]);
    }
    free(adj);
    free(adjSize);
    free(dist);
    free(parents);
    free(parentCnt);
    free(queue);

    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = strlen(result[i]);
    }
    return result;

}
