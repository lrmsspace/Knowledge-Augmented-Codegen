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
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
//   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
//   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
//   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
//   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
//   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes) {
    // Step 1: Calculate the total number of pairs and adjust k if necessary
    int totalPairs = nums1Size * nums2Size;
    if (k > totalPairs) {
        k = totalPairs;
    }

    // Step 2: Allocate memory for the result array and column sizes
    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    
    // Step 3: Use a min-heap to find the k smallest pairs
    typedef struct {
        int sum; // sum of the pair
        int i;   // index in nums1
        int j;   // index in nums2
    } Pair;

    Pair* minHeap = (Pair*)malloc(totalPairs * sizeof(Pair));
    int heapSize = 0;

    // Initialize the heap with pairs from the first element of nums1 and all elements of nums2
    for (int j = 0; j < nums2Size && j < k; j++) {
        minHeap[heapSize++] = (Pair){nums1[0] + nums2[j], 0, j};
    }

    // Function to maintain the min-heap property
    void heapifyDown(int index) {
        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < heapSize && minHeap[left].sum < minHeap[smallest].sum) {
                smallest = left;
            }
            if (right < heapSize && minHeap[right].sum < minHeap[smallest].sum) {
                smallest = right;
            }
            if (smallest == index) break;

            Pair temp = minHeap[index];
            minHeap[index] = minHeap[smallest];
            minHeap[smallest] = temp;
            index = smallest;
        }
    }

    // Extract the k smallest pairs from the heap
    for (int count = 0; count < k; count++) {
        Pair currentPair = minHeap[0];
        result[count] = (int*)malloc(2 * sizeof(int));
        result[count][0] = nums1[currentPair.i];
        result[count][1] = nums2[currentPair.j];
        (*returnColumnSizes)[count]     
            = 2;
        // Move the next pair from the same row (i) to the heap
        if (currentPair.i + 1 < nums1Size) {
            minHeap[0] = (Pair){nums1[currentPair.i + 1] + nums2[currentPair.j], currentPair.i + 1, currentPair.j};
        } else {
            // If there are no more pairs in this row, remove the top element
            minHeap[0] = minHeap[--heapSize];
        }
        heapifyDown(0);
    }
    *returnSize = k;
    free(minHeap);
    return result;
}
