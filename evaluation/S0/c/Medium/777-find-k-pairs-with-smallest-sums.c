// Source: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 sorted in non-decreasing order and an integer k.
//
// Define a pair (u, v) which consists of one element from the first array and one element from the second array.
//
// Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.
//
// Example:
// Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
// Output: [[1,2],[1,4],[1,6]]
// Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	-109 <= nums1[i], nums2[i] <= 109
// 	nums1 and nums2 both are sorted in non-decreasing order.
// 	1 <= k <= 104
// 	k <= nums1.length * nums2.length
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(sizeof(int*) * k);
    *returnColumnSizes = (int*)malloc(sizeof(int) * k);
    *returnSize = 0;

    typedef struct {
        int sum;
        int i;
        int j;
    } Pair;

    typedef struct {
        Pair* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (Pair*)malloc(sizeof(Pair) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(Pair* a, Pair* b) {
        Pair temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent].sum <= heap->data[index].sum) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void heapifyDown(MinHeap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;

            if (right < heap->size && heap->data[right].sum < heap->data[left].sum) {
                smallest = right;
            }

            if (heap->data[index].sum <= heap->data[smallest].sum) break;

            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        }
    }

    void push(MinHeap* heap, Pair pair) {
        if (heap->size == heap->capacity) return;
        heap->data[heap->size] = pair;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    Pair pop(MinHeap* heap) {
        Pair top = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
        return top;
    }
    MinHeap* heap = createHeap(k);
    for (int i = 0; i < nums1Size && i < k; i++) {
        Pair pair = {nums1[i] + nums2[0], i, 0};
        push(heap, pair);
    }
    while (*returnSize < k && heap->size > 0) {
        Pair current = pop(heap);
        int i = current.i;
        int j = current.j;

        result[*returnSize] = (int*)malloc(2 * sizeof(int));
        result[*returnSize][0] = nums1[i];
        result[*returnSize][1] = nums2[j];
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;

        if (j + 1 < nums2Size) {
            Pair nextPair = {nums1[i] + nums2[j + 1], i, j + 1};
            push(heap, nextPair);
        }
    }
    free(heap->data);
    free(heap);
    return result;
}
