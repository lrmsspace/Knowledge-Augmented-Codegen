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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* nums, int numsSize, int k) {
    // Min-heap implementation
    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapify(int* heap, int size, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            swap(&heap[index], &heap[smallest]);
            heapify(heap, size, smallest);
        }
    }

    void buildHeap(int* heap, int size) {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(heap, size, i);
    }

    int extractMin(int* heap, int* size) {
        if (*size <= 0)
            return -1;
        if (*size == 1) {
            (*size)--;
            return heap[0];
        }

        int root = heap[0];
        heap[0] = heap[*size - 1];
        (*size)--;
        heapify(heap, *size, 0);

        return root;
    }

    void insert(int* heap, int* size, int value) {
        heap[*size] = value;
        (*size)++;
        int i = *size - 1;

        while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Main logic
    int heapSize = numsSize;
    buildHeap(nums, heapSize);
    int operations = 0;

    while (heapSize > 0 && nums[0] < k) {
        int firstMin = extractMin(nums, &heapSize);
        int secondMin = extractMin(nums, &heapSize);
        int newElement = firstMin * 2 + secondMin;
        insert(nums, &heapSize, newElement);
        operations++;
        if (heapSize < 2 && nums[0] < k) {
            return -1; // Not enough elements to perform operation
        }
    }
    return operations;
}
