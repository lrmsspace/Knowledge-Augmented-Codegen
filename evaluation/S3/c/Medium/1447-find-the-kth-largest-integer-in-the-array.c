// Source: https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings nums and an integer k. Each string in nums represents an integer without leading zeros.
//
// Return the string that represents the kth largest integer in nums.
//
// Note: Duplicate numbers should be counted distinctly. For example, if nums is ["1","2","2"], "2" is the first largest integer, "2" is the second-largest integer, and "1" is the third-largest integer.
//
// Example:
// Input: nums = ["3","6","7","10"], k = 4
// Output: "3"
// Explanation:
// The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
// The 4th largest integer in nums is "3".
//
// Constraints:
// 1 <= k <= nums.length <= 104
// 	1 <= nums[i].length <= 100
// 	nums[i] consists of only digits.
// 	nums[i] will not have any leading zeros.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - kth-largest-element-in-an-array (array, quickselect, randomized)
//   • When to use: Use when you need to efficiently find the k-th smallest or largest element in an unsorted array without fully sorting it, especially when average-case linear time complexity is acceptable and in-place modification is desired.
//   • Idea: QuickSelect is a divide-and-conquer algorithm that partitions an array around a pivot and recursively searches for the k-th element in the relevant partition. It offers an average-case O(N) time complexity and O(1) space.
//   • Invariants: The pivot element is always placed at its correct sorted position within the current sub-array.; All elements to the left of the pivot are less than or equal to it, and all elements to its right are greater than or equal to it.
//   • Tips: Randomly select pivots to ensure average-case O(N) performance and avoid worst-case scenarios.; Adjust the target index k based on whether you're seeking the k-th smallest or k-th largest element.
//   • Pitfalls: Poor pivot selection can lead to a worst-case O(N^2) time complexity, though rare with randomization.; Off-by-one errors are common when mapping k-th largest/smallest to 0-indexed array positions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* kthLargestNumber(char** nums, int numsSize, int k) {
    // Step 1: Sort the array of strings based on their integer values.
    // We can use a custom comparison function that compares the lengths of the strings first,
    // and if they are of the same length, we can compare them lexicographically.
    
    // Custom comparison function for qsort
    int compare(const void* a, const void* b) {
        const char* strA = *(const char**)a;
        const char* strB = *(const char**)b;
        
        int lenA = strlen(strA);
        int lenB = strlen(strB);
        
        // Compare by length
        if (lenA != lenB) {
            return lenA - lenB; // shorter string is smaller
        }
        
        // If lengths are equal, compare lexicographically
        return strcmp(strA, strB); // lexicographical order
    }
    
    // Sort the array using qsort and the custom comparison function
    qsort(nums, numsSize, sizeof(char*), compare);
    
    // Step 2: The k-th largest element will be at index numsSize - k after sorting
    return nums[numsSize - k];      
}
