// Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
//
// Problem Description:
// Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
//
// You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
//
// A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
//
//
// 	The number of complete gardens multiplied by full.
// 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
//
//
// Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
//
// Example:
// Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
// Output: 14
// Explanation: Alice can plant
// - 2 flowers in the 0th garden
// - 3 flowers in the 1st garden
// - 1 flower in the 2nd garden
// - 1 flower in the 3rd garden
// The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
// There is 1 garden that is complete.
// The minimum number of flowers in the incomplete gardens is 2.
// Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
// No other way of planting flowers can obtain a total beauty higher than 14.
//
// Constraints:
// 1 <= flowers.length <= 105
// 	1 <= flowers[i], target <= 105
// 	1 <= newFlowers <= 1010
// 	1 <= full, partial <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maximumBeauty(int* flowers, int flowersSize, long long newFlowers, int target, int full, int partial) {
    /* Separate complete and incomplete gardens */
    int complete = 0;
    int *incomplete = (int*)malloc(flowersSize * sizeof(int));
    if (!incomplete) return 0; /* allocation failure */
    int incSize = 0;
    for (int i = 0; i < flowersSize; ++i) {
        if (flowers[i] >= target) {
            complete++;
        } else {
            incomplete[incSize++] = flowers[i];
        }
    }
    /* Sort incomplete gardens */
    qsort(incomplete, incSize, sizeof(int), cmpInt);

    /* Prefix sums for incomplete gardens */
    long long *prefixSums = (long long*)malloc((incSize + 1) * sizeof(long long));
    if (!prefixSums) { free(incomplete); return 0; } /* allocation failure */
    prefixSums[0] = 0;
    for (int i = 0; i < incSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + incomplete[i];
    }

    long long maxBeauty = 0;
    /* Try making k gardens complete */
    for (int k = 0; k <= incSize; ++k) {
        long long flowersNeeded = 0;
        if (k > 0) {
            for (int i = incSize - k; i < incSize; ++i) {
                flowersNeeded += (target - incomplete[i]);
            }
        }
        if (flowersNeeded > newFlowers) break;

        long long remainingFlowers = newFlowers - flowersNeeded;

        /* Binary search for maximum minimum in incomplete gardens */
        long long low = 0, high = target - 1;
        while (low < high) {
            long long mid = (low + high + 1) / 2;
            /* Calculate flowers needed to raise all incomplete gardens to at least mid */
            int pos = 0;
            while (pos < incSize - k && incomplete[pos] < mid) pos++;
            long long needed = mid * pos - prefixSums[pos];
            if (needed <= remainingFlowers) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        long long currentBeauty = (long long)(complete + k) * full + low * partial;
        if (currentBeauty > maxBeauty) {
            maxBeauty = currentBeauty;
        }

}
    free(incomplete);
    free(prefixSums);
    return maxBeauty;
}