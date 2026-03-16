// Source: https://leetcode.com/problems/number-of-flowers-in-full-bloom/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where people[i] is the time that the ith person will arrive to see the flowers.
//
// Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith person arrives.
//
// Example:
// Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
// Output: [1,2,2,2]
// Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
// For each person, we return the number of flowers in full bloom during their arrival.
//
// Constraints:
// 1 <= flowers.length <= 5 * 104
// 	flowers[i].length == 2
// 	1 <= starti <= endi <= 109
// 	1 <= people.length <= 5 * 104
// 	1 <= people[i] <= 109
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
int* fullBloomFlowers(int** flowers, int flowersSize, int* flowersColSize, int* people, int peopleSize, int* returnSize) {
    int *startTimes = (int*)malloc(flowersSize * sizeof(int));
    int *endTimes = (int*)malloc(flowersSize * sizeof(int));
    for (int i = 0; i < flowersSize; i++) {
        startTimes[i] = flowers[i][0];
        endTimes[i] = flowers[i][1];
    }
    // Sort start and end times
    qsort(startTimes, flowersSize, sizeof(int), cmpInt);
    qsort(endTimes, flowersSize, sizeof(int), cmpInt);

    int* result = (int*)malloc(peopleSize * sizeof(int));
    for (int i = 0; i < peopleSize; i++) {
        int arrival = people[i];
        // Count flowers that have started blooming
        int left = 0, right = flowersSize - 1, startCount = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (startTimes[mid] <= arrival) {
                startCount = mid + 1;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        // Count flowers that have ended blooming
        left = 0; right = flowersSize - 1;
        int endCount = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (endTimes[mid] < arrival) {
                endCount = mid + 1;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        result[i] = startCount - endCount;
    }

    free(startTimes);
    free(endTimes);
    *returnSize = peopleSize;
    return result;      
}
