// Source: https://leetcode.com/problems/construct-target-array-with-multiple-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :
//
//
// 	let x be the sum of all elements currently in your array.
// 	choose index i, such that 0 <= i < n and set the value of arr at index i to x.
// 	You may repeat this procedure as many times as needed.
//
//
// Return true if it is possible to construct the target array from arr, otherwise, return false.
//
// Example:
// Input: target = [9,3,5]
// Output: true
// Explanation: Start with arr = [1, 1, 1] 
// [1, 1, 1], sum = 3 choose index 1
// [1, 3, 1], sum = 5 choose index 2
// [1, 3, 5], sum = 9 choose index 0
// [9, 3, 5] Done
//
// Constraints:
// n == target.length
// 	1 <= n <= 5 * 104
// 	1 <= target[i] <= 109
//

bool isPossible(int* target, int targetSize) {
    long long total = 0;
    for (int i = 0; i < targetSize; ++i) {
        total += target[i];
    }

    /* max-heap */
    int *heap = (int*)malloc(targetSize * sizeof(int));
    if (!heap) return false;
    int heapSize = 0;

    #define SWAP(a, b) do { int tmp = a; a = b; b = tmp; } while(0)
    #define HEAP_PUSH(x) do { \
        heap[heapSize] = x; \
        int idx = heapSize++; \
        while (idx > 0) { \
            int parent = (idx - 1) / 2; \
            if (heap[parent] >= heap[idx]) break; \
            SWAP(heap[parent], heap[idx]); \
            idx = parent; \
        } \
    } while(0)
    #define HEAP_POP() ({ \
        int ret = heap[0]; \
        heap[0] = heap[--heapSize]; \
        int idx = 0; \
        while (1) { \
            int left = idx * 2 + 1, right = idx * 2 + 2, largest = idx; \
            if (left < heapSize && heap[left] > heap[largest]) largest = left; \
            if (right < heapSize && heap[right] > heap[largest]) largest = right; \
            if (largest == idx) break; \
            SWAP(heap[idx], heap[largest]); \
            idx = largest; \
        } \
        ret; \
    })

    for (int i = 0; i < targetSize; ++i) {
        HEAP_PUSH(target[i]);
    }

    while (1) {
        int top = HEAP_POP();
        long long rest = total - top;
        if (top == 1 || rest == 1) {
            free(heap);
            return true;
        }
        if (rest == 0 || rest >= top) {
            free(heap);
            return false;
        }
        int newVal = top % rest;
        if (newVal == 0) {
            free(heap);
            return false;
        }
        total = rest + newVal;
        HEAP_PUSH(newVal);
    }

    free(heap);
    return false;       
}
