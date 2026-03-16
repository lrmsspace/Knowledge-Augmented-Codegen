// Source: https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums, an integer array queries, and an integer x.
//
// For each queries[i], you need to find the index of the queries[i]th occurrence of x in the nums array. If there are fewer than queries[i] occurrences of x, the answer should be -1 for that query.
//
// Return an integer array answer containing the answers to all queries.
//
// Example:
// Input: nums = [1,3,1,7], queries = [1,3,2,4], x = 1
//
// Output: [0,-1,2,-1]
//
// Explanation:
//
//
// 	For the 1st query, the first occurrence of 1 is at index 0.
// 	For the 2nd query, there are only two occurrences of 1 in nums, so the answer is -1.
// 	For the 3rd query, the second occurrence of 1 is at index 2.
// 	For the 4th query, there are only two occurrences of 1 in nums, so the answer is -1.
//
// Constraints:
// 1 <= nums.length, queries.length <= 105
// 	1 <= queries[i] <= 105
// 	1 <= nums[i], x <= 104
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
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
int* occurrencesOfElement(int* nums, int numsSize, int* queries, int queriesSize, int x, int* returnSize) {
    // Step 1: Create a hash map to store the occurrences of x
    int* occurrences = (int*)malloc(numsSize * sizeof(int));
    int count = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == x) {
            occurrences[count++] = i;
        }
    }
    
    // Step 2: Prepare the result array
    int* result = (int*)malloc(queriesSize * sizeof(int));
    
    for (int i = 0; i < queriesSize; i++) {
        int occurrenceIndex = queries[i] - 1; // Convert to 0-based index
        if (occurrenceIndex < count) {
            result[i] = occurrences[occurrenceIndex];
        } else {
            result[i] = -1; // Not enough occurrences
        }
    }
    
    // Step 3: Set the return size and free the occurrences array
    *returnSize = queriesSize;
    free(occurrences);
    
    return result;      
}
