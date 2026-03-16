// Source: https://leetcode.com/problems/intersection-of-multiple-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D integer array nums where nums[i] is a non-empty array of distinct positive integers, return the list of integers that are present in each array of nums sorted in ascending order.
//
// Example:
// Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
// Output: [3,4]
// Explanation: 
// The only integers present in each of nums[0] = [3,1,2,4,5], nums[1] = [1,2,3,4], and nums[2] = [3,4,5,6] are 3 and 4, so we return [3,4].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= sum(nums[i].length) <= 1000
// 	1 <= nums[i][j] <= 1000
// 	All the values of nums[i] are unique.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Lowest Common Ancestor (array, sparse-table)
//   • When to use: Use this when you need to find the lowest common ancestor of many pairs of nodes in a static tree efficiently. It excels in scenarios with numerous queries after initial setup.
//   • Idea: This technique finds the LCA by transforming the problem into a Range Minimum Query (RMQ) on an Euler tour of the tree. It achieves O(N log N) precomputation time and O(1) query time.
//   • Invariants: The sparse_table[k][i] stores the minimum depth in the Euler tour array segment starting at index i and spanning 2^k elements.; The first_occurrence array correctly maps each node to its initial appearance index in the Euler tour.
//   • Tips: Perform an Euler tour (DFS traversal) to linearize the tree into an array of nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Off-by-one errors when calculating range lengths or sparse table indices.; Incorrectly handling the Euler tour array, especially when mapping back to original nodes.
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
int* intersection(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    int count[1001] = {0}; // Count occurrences of each number
    int totalArrays = numsSize;

    // Count occurrences of each number in all arrays
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsColSize[i]; j++) {
            int num = nums[i][j];
            count[num]++;
        }
    }

    // Collect numbers that are present in all arrays
    int* result = (int*)malloc(sizeof(int) * 1000); // Max possible size
    int index = 0;
    for (int num = 1; num <= 1000; num++) {
        if (count[num] == totalArrays) {
            result[index++] = num;
        }
    }

    *returnSize = index; // Set the return size to the number of common elements
    return result; // Return the array of common elements       
}
