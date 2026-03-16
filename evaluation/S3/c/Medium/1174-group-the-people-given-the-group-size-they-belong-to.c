// Source: https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/   |   Difficulty: Medium
//
// Problem Description:
// There are n people that are split into some unknown number of groups. Each person is labeled with a unique ID from 0 to n - 1.
//
// You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.
//
// Return a list of groups such that each person i is in a group of size groupSizes[i].
//
// Each person should appear in exactly one group, and every person must be in a group. If there are multiple answers, return any of them. It is guaranteed that there will be at least one valid solution for the given input.
//
// Example:
// Input: groupSizes = [3,3,3,3,3,1,3]
// Output: [[5],[0,1,2],[3,4,6]]
// Explanation: 
// The first group is [5]. The size is 1, and groupSizes[5] = 1.
// The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] = groupSizes[2] = 3.
// The third group is [3,4,6]. The size is 3, and groupSizes[3] = groupSizes[4] = groupSizes[6] = 3.
// Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].
//
// Constraints:
// groupSizes.length == n
// 	1 <= n <= 500
// 	1 <= groupSizes[i] <= n
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - bucket-sort (array, bucket-sort)
//   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
//   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
//   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
//   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
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
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes) {
    // Step 1: Count the frequency of each group size
    int count[501] = {0}; // Since groupSizes[i] <= n and n <= 500
    for (int i = 0; i < groupSizesSize; i++) {
        count[groupSizes[i]]++;
    }

    // Step 2: Calculate the total number of groups needed
    int totalGroups = 0;
    for (int i = 1; i <= 500; i++) {
        if (count[i] > 0) {
            totalGroups += (count[i] + i - 1) / i; // Ceiling division to get number of groups for size i
        }
    }

    // Step 3: Allocate memory for return values
    int** result = (int**)malloc(totalGroups * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalGroups * sizeof(int));
    
    // Step 4: Fill the result array with groups
    int groupIndex = 0;
    for (int size = 1; size <= 500; size++) {
        if (count[size] > 0) {
            int numGroups = (count[size] + size - 1) / size; // Number of groups for this size
            int* currentGroup = (int*)malloc(size * sizeof(int)); // Temporary array to hold current group members
            int currentIndex = 0;

            for (int i = 0; i < groupSizesSize; i++) {
                if (groupSizes[i] == size) {
                    currentGroup[currentIndex++] = i;
                    if (currentIndex == size) { // If we filled a group
                        result[groupIndex] = currentGroup; // Assign the group to result
                        (*returnColumnSizes)[groupIndex] = size; // Set the column size for this group
                        groupIndex++; // Move to the next group index
                        currentGroup = (int*)malloc(size * sizeof(int)); // Allocate new array for next group
                        currentIndex = 0; // Reset index for new group
                    }
                }
            }
            free(currentGroup); // Free the last allocated group if it wasn't used
        }
    }

    *returnSize = totalGroups; // Set the return size to the total number of groups
    return result;      
}
