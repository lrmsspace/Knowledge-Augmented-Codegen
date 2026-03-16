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
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
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
    int maxPairs = nums1Size * nums2Size;
    if (k > maxPairs) {
        k = maxPairs;
    }

    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    *returnSize = 0;

    typedef struct {
        int sum;
        int i;
        int j;
    } Pair;

    Pair* minHeap = (Pair*)malloc(k * sizeof(Pair));
    int heapSize = 0;

    for (int i = 0; i < nums1Size && i < k; i++) {
        Pair p = {nums1[i] + nums2[0], i, 0};
        minHeap[heapSize++] = p;
    }

    for (int count = 0; count < k && heapSize > 0; count++) {
        Pair minPair = minHeap[0];
        result[count] = (int*)malloc(2 * sizeof(int));
        result[count][0] = nums1[minPair.i];
        result[count][1] = nums2[minPair.j];
        (*returnColumnSizes)[count] = 2;
        (*returnSize)++;

        if (minPair.j + 1 < nums2Size) {
            minPair.sum = nums1[minPair.i] + nums2[minPair.j + 1];
            minPair.j += 1;
            minHeap[0] = minPair;
        } else {
            minHeap[0] = minHeap[--heapSize];
        }

        int idx = 0;
        while (true) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;

            if (left < heapSize && minHeap[left].sum < minHeap[smallest].sum) {
                smallest = left;
            }
            if (right < heapSize && minHeap[right].sum < minHeap[smallest].sum) {
                smallest = right;
            }
            if (smallest == idx) {
                break;
            }
            Pair temp = minHeap[idx];
            minHeap[idx] = minHeap[smallest];
            minHeap[smallest] = temp;
            idx = smallest;
        }
    }

    free(minHeap);
    return result;
}
