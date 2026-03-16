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
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
//   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
//   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
//   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
//   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
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
    // Step 1: Create an array of pairs (nums1[i], nums2[i]) and sort it based on nums1[i].
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

    // Step 2: Use a min-heap to keep track of the k largest nums2 values encountered so far.
    long long* result = (long long*)malloc(nums1Size * sizeof(long long));
    int heapSize = 0;
    long long heap[100000]; // Min-heap to store the k largest nums2 values
    long long sum = 0;

    for (int i = 0; i < nums1Size; i++) {
        // Remove elements from the heap that are less than the current num1
        while (heapSize > 0 && pairs[heap[0]].num1 < pairs[i].num1) {
            sum -= pairs[heap[0]].num2;
            heap[0] = heap[--heapSize]; // Remove the top element
            // Heapify down
            int idx = 0;
            while (true) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int smallest = idx;

                if (left < heapSize && pairs[heap[left]].num2 < pairs[heap[smallest]].num2) {
                    smallest = left;
                }
                if (right < heapSize && pairs[heap[right]].num2 < pairs[heap[smallest]].num2) {
                    smallest = right;
                }
                if (smallest == idx) break;

                // Swap
                int temp = heap[idx];
                heap[idx] = heap[smallest];
                heap[smallest] = temp;
                idx = smallest;
            }
        }

        // Add      
        if (heapSize < k) {
                heap[heapSize++] = i;
                sum += pairs[i].num2;
            } else if (heapSize > 0 && pairs[i].num2 > pairs[heap[0]].num2) {
                sum += pairs[i].num2 - pairs[heap[0]].num2;
                heap[0] = i; // Replace the smallest element
                // Heapify down
                int idx = 0;
                while (true) {
                    int left = 2 * idx + 1;
                    int right = 2 * idx + 2;
                    int smallest = idx;
    
                    if (left < heapSize && pairs[heap[left]].num2 < pairs[heap[smallest]].num2) {
                        smallest = left;
                    }
                    if (right < heapSize && pairs[heap[right]].num2 < pairs[heap[smallest]].num2) {
                        smallest = right;
                    }
                    if (smallest == idx) break;
    
                    // Swap
                    int temp = heap[idx];
                    heap[idx] = heap[smallest];
                    heap[smallest] = temp;
                    idx = smallest;
                }
            }   
            result[i] = sum;
        }
        *returnSize = nums1Size;
        free(pairs);
        return result;
    }
