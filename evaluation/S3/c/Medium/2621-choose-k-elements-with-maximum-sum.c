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
// Helpful references (internal KB):
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* findMaxSum(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize) {
    // Step 1: Create an array of pairs (nums1[i], nums2[i]) and sort it based on nums1[i]
    typedef struct {
        int num1;
        int num2;
    } Pair;

    Pair* pairs = (Pair*)malloc(nums1Size * sizeof(Pair));
    for (int i = 0; i < nums1Size; i++) {
        pairs[i].num1 = nums1[i];
        pairs[i].num2 = nums2[i];
    }

    // Sort pairs based on num1
    qsort(pairs, nums1Size, sizeof(Pair), [](const void* a, const void* b) {
        return ((Pair*)a)->num1 - ((Pair*)b)->num1;
    });

    // Step 2: Use a max heap to keep track of the top k values of nums2[j]
    long long* result = (long long*)malloc(nums1Size * sizeof(long long));
    for (int i = 0; i < nums1Size; i++) {
        result[i] = 0; // Initialize result array
    }

    // Max heap to store the top k values of nums2[j]
    typedef struct {
        int value;
        int index;
    } HeapNode;

    HeapNode* maxHeap = (HeapNode*)malloc(nums1Size * sizeof(HeapNode));
    int heapSize = 0;

    for (int i = 0; i < nums1Size; i++) {
        // Add current pair's num2 to the max heap
        if (heapSize < k) {
            maxHeap[heapSize++] = (HeapNode){pairs[i].num2, i};
            // Heapify up
            for (int j = heapSize - 1; j > 0; j--) {
                if (maxHeap[j].value > maxHeap[(j - 1) / 2].value) {
                    HeapNode temp = maxHeap[j];
                    maxHeap[j] = maxHeap[(j - 1) / 2];
                    maxHeap[(j - 1) / 2] = temp;
                } else {
                    break;
                }
            }
        } else if (pairs[i].num2 > maxHeap[0].value) {
            maxHeap[0] = (HeapNode){pairs[i].num2, i};     
            // Heapify down
            int j = 0;
            while (2 * j + 1 < heapSize) {
                int left = 2 * j + 1;
                int right = 2 * j + 2;
                int largest = j;

                if (left < heapSize && maxHeap[left].value > maxHeap[largest].value) {
                    largest = left;
                }
                if (right < heapSize && maxHeap[right].value > maxHeap[largest].value) {
                    largest = right;
                }
                if (largest != j) {
                    HeapNode temp = maxHeap[j];
                    maxHeap[j] = maxHeap[largest];
                    maxHeap[largest] = temp;
                    j = largest;
                } else {
                    break;
                }
            }
            result[i] = 0;
            for (int j = 0; j < heapSize; j++) {
                result[i] += maxHeap[j].value;
            }
        }
    
        // Update result for current index
        if (heapSize == k) {
            result[i] = 0;
            for (int j = 0; j < heapSize; j++) {
                result[i] += maxHeap[j].value;
            }
        
        }
    }
    *returnSize = nums1Size;
    return result;
}
