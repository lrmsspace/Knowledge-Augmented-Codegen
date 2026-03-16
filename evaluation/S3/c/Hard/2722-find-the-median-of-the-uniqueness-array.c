// Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
//
// Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
//
// Return the median of the uniqueness array of nums.
//
// Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 1
//
// Explanation:
//
// The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int medianOfUniquenessArray(int* nums, int numsSize) {
    // The maximum number of distinct elements in any subarray is at most numsSize.
    // We can count the frequency of each distinct element and use a sliding window to find the number of distinct elements in each subarray.
    // We will use a frequency array to keep track of the count of each element in the current window.
    // We will also maintain a count of how many distinct elements are currently in the window.

    int freq[100001] = {0}; // Frequency array for counting occurrences of each element
    int distinctCount = 0; // Count of distinct elements in the current window
    int totalSubarrays = numsSize * (numsSize + 1) / 2; // Total number of subarrays
    int* uniquenessArray = (int*)malloc(totalSubarrays * sizeof(int)); // Array to store the number of distinct elements for each subarray
    int index = 0; // Index for filling uniquenessArray

    for (int start = 0; start < numsSize; start++) {
        for (int end = start; end < numsSize; end++) {
            // Add the current element to the frequency array
            if (freq[nums[end]] == 0) {
                distinctCount++; // New distinct element found
            }
            freq[nums[end]]++;

            // Store the number of distinct elements in the uniqueness array
            uniquenessArray[index++] = distinctCount;
        }

        // Reset frequency array and distinct count for the next starting point
        for (int i = start; i < numsSize; i++) {
            freq[nums[i]] = 0;
        }
        distinctCount = 0;
    }

    // Now we need to find the median of the uniqueness array
    // Sort the uniqueness array
    qsort(uniquenessArray, totalSubarrays, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int median;
    if (totalSubarrays % 2 == 1) {
        median = uniquenessArray[totalSubarrays / 2]; // Odd length, take the middle element
    } else {
        median = uniquenessArray[(totalSubarrays / 2) - 1]; // Even length, take the smaller of the two middle elements
    }

    free(uniquenessArray); // Free allocated memory
    return median;      
}
