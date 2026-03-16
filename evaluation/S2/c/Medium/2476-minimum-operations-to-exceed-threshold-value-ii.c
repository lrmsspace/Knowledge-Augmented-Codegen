// Source: https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums, and an integer k.
//
// You are allowed to perform some operations on nums, where in a single operation, you can:
//
//
// 	Select the two smallest integers x and y from nums.
// 	Remove x and y from nums.
// 	Insert (min(x, y) * 2 + max(x, y)) at any position in the array.
//
//
// Note that you can only apply the described operation if nums contains at least two elements.
//
// Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.
//
// Example:
// Input: nums = [2,11,10,1,3], k = 10
//
// Output: 2
//
// Explanation:
//
//
// 	In the first operation, we remove elements 1 and 2, then add 1 * 2 + 2 to nums. nums becomes equal to [4, 11, 10, 3].
// 	In the second operation, we remove elements 3 and 4, then add 3 * 2 + 4 to nums. nums becomes equal to [10, 11, 10].
//
//
// At this stage, all the elements of nums are greater than or equal to 10 so we can stop. 
//
// It can be shown that 2 is the minimum number of operations needed so that all elements of the array are greater than or equal to 10.
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
// 	The input is generated such that an answer always exists. That is, after performing some number of operations, all elements of the array are greater than or equal to k.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* nums, int numsSize, int k) {
    // We can use a min-heap to always combine the two smallest elements efficiently.
    // The heap will allow us to perform the required operations in O(log n) time for each operation.
    
    // Step 1: Build a min-heap from the input array.
    // Step 2: While the smallest element in the heap is less than k, perform the operation:
    //         - Pop the two smallest elements (x and y).
    //         - Calculate the new value as (min(x, y) * 2 + max(x, y)).
    //         - Push the new value back into the heap.
    // Step 3: Count the number of operations performed until all elements are >= k.

    // Since we need to implement a min-heap, we can use an array to represent it and write helper functions for heap operations.

    int operations = 0;

    // Helper function to swap two elements in the heap
    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    // Helper function to maintain the min-heap property after insertion
    void heapifyUp(int* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                swap(&heap[index], &heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Helper function to maintain the min-heap property after removal
    void heapifyDown(int* heap, int size, int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                swap(&heap[index], &heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

    // Build the initial min-heap
    int* heap = malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        heap[i] = nums[i];
        heapifyUp(heap, i);
    }

    // Perform operations until all elements in the heap are >= k
    while (heap[0] < k && numsSize > 1) {
        int x = heap[0];
        heap[0] = heap[numsSize - 1];
        numsSize--;
        heapifyDown(heap, numsSize, 0);
        int y = heap[0];
        heap[0] = (x < y ? x * 2 + y : y * 2 + x);
        operations++;
    }

    free(heap);
    return operations;
}