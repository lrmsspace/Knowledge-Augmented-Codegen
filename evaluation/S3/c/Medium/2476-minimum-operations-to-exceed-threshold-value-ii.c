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
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* nums, int numsSize, int k) {
    // We can use a min-heap to efficiently get the two smallest elements.
    // The heap will be implemented as an array, and we will maintain the heap property after each operation.
    
    // Step 1: Build the min-heap from the input array.
    for (int i = numsSize / 2 - 1; i >= 0; i--) {
        // Heapify down from index i
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < numsSize && nums[left] < nums[smallest]) {
            smallest = left;
        }
        if (right < numsSize && nums[right] < nums[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            // Swap
            int temp = nums[i];
            nums[i] = nums[smallest];
            nums[smallest] = temp;
            // Heapify down the affected subtree
            int j = smallest;
            while (j < numsSize) {
                smallest = j;
                left = 2 * j + 1;
                right = 2 * j + 2;
                
                if (left < numsSize && nums[left] < nums[smallest]) {
                    smallest = left;
                }
                if (right < numsSize && nums[right] < nums[smallest]) {
                    smallest = right;
                }
                if (smallest != j) {
                    // Swap
                    temp = nums[j];
                    nums[j] = nums[smallest];
                    nums[smallest] = temp;
                    j = smallest;
                } else {
                    break;
                }
            }
        }
    }
    
    int operations = 0;
    
    // Step 2: Perform operations until all elements are >= k
    while (nums[0] < k) {
        if (numsSize < 2) {
            return -1; // Not enough elements to perform an operation
        }
        
        // Get the two smallest elements
        int x = nums[0];
        
        // Remove the smallest element
        nums[0] = nums[numsSize - 1];
        numsSize--;
        
        // Heapify down from the root to restore the heap property
        int j = 0;
        while (j < numsSize) {
            int smallest = j;
            int left = 2 * j + 1;
            int right = 2 * j + 2;
            
            if (left < numsSize && nums[left] < nums[smallest]) {
                smallest = left;
            }
            if (right < numsSize && nums[right] < nums[smallest]) {
                smallest = right;
            }
            if (smallest != j) {
                // Swap
                int temp = nums[j];
                nums[j] = nums[smallest];
                nums[smallest] = temp;
                j = smallest;
            } else {
                break;
            }
        }
        operations++;
    }
    return operations;
}
