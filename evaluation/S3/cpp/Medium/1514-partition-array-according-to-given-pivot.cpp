// Source: https://leetcode.com/problems/partition-array-according-to-given-pivot/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer pivot. Rearrange nums such that the following conditions are satisfied:
//
//
// 	Every element less than pivot appears before every element greater than pivot.
// 	Every element equal to pivot appears in between the elements less than and greater than pivot.
// 	The relative order of the elements less than pivot and the elements greater than pivot is maintained.
// 	
// 		More formally, consider every pi, pj where pi is the new position of the ith element and pj is the new position of the jth element. If i < j and both elements are smaller (or larger) than pivot, then pi < pj.
// 	
// 	
//
//
// Return nums after the rearrangement.
//
// Example:
// Input: nums = [9,12,5,10,14,3,10], pivot = 10
// Output: [9,5,3,10,10,12,14]
// Explanation: 
// The elements 9, 5, and 3 are less than the pivot so they are on the left side of the array.
// The elements 12 and 14 are greater than the pivot so they are on the right side of the array.
// The relative ordering of the elements less than and greater than pivot is also maintained. [9, 5, 3] and [12, 14] are the respective orderings.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-106 <= nums[i] <= 106
// 	pivot equals to an element of nums.
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Quicksort (array, two-pointers, randomized)
//   • When to use: Use Quicksort for efficient in-place sorting of arrays, especially when average-case performance and cache efficiency are prioritized. It is suitable for large datasets where memory usage is a concern.
//   • Idea: Quicksort is a divide-and-conquer sorting algorithm that partitions an array around a pivot element, then recursively sorts the two resulting subarrays. Its average time complexity is O(N log N), but can degrade to O(N^2) in the worst case.
//   • Invariants: All elements to the left of the `lt` pointer are less than the pivot value.; All elements to the right of the `gt` pointer are greater than the pivot value.
//   • Tips: Randomly shuffle the input or choose a random pivot to ensure average-case performance.; Employ 3-way partitioning to efficiently handle duplicate keys and avoid quadratic worst-case scenarios.
//   • Pitfalls: Failing to handle duplicate keys can lead to quadratic time complexity.; Incorrect pointer crossing logic can cause infinite loops or array out-of-bounds errors.
// - Quicksort (array, recursion, randomized)
//   • When to use: Use when an efficient in-place sorting algorithm is needed, especially for large datasets where average-case performance is critical. It's a good general-purpose choice.
//   • Idea: Quicksort is a divide-and-conquer sorting algorithm that partitions an array around a pivot element, then recursively sorts the two resulting subarrays. It has an average time complexity of O(N log N) and a worst-case complexity of O(N^2).
//   • Invariants: After partitioning, the pivot element is at its final sorted position.; All elements to the left of the pivot are less than or equal to the pivot.
//   • Tips: Choose a good pivot strategy (e.g., random pivot, median-of-three) to avoid worst-case scenarios.; Handle small subarrays with insertion sort to reduce recursion overhead.
//   • Pitfalls: Poor pivot selection can lead to O(N^2) worst-case time complexity.; Excessive recursion depth can cause stack overflow for very large inputs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> ans(nums.size());
        int i = 0, j = nums.size() - 1;
        for (int num : nums) {
            if (num < pivot) {
                ans[i++] = num;
            } else if (num > pivot) {
                ans[j--] = num;
            }
        }
        while (i <= j) {
            ans[i++] = pivot;
        }
        return ans;         
    }
};
