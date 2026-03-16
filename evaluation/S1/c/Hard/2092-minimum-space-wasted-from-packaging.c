// Source: https://leetcode.com/problems/minimum-space-wasted-from-packaging/   |   Difficulty: Hard
//
// Problem Description:
// You have n packages that you are trying to place in boxes, one package in each box. There are m suppliers that each produce boxes of different sizes (with infinite supply). A package can be placed in a box if the size of the package is less than or equal to the size of the box.
//
// The package sizes are given as an integer array packages, where packages[i] is the size of the ith package. The suppliers are given as a 2D integer array boxes, where boxes[j] is an array of box sizes that the jth supplier produces.
//
// You want to choose a single supplier and use boxes from them such that the total wasted space is minimized. For each package in a box, we define the space wasted to be size of the box - size of the package. The total wasted space is the sum of the space wasted in all the boxes.
//
//
// 	For example, if you have to fit packages with sizes [2,3,5] and the supplier offers boxes of sizes [4,8], you can fit the packages of size-2 and size-3 into two boxes of size-4 and the package with size-5 into a box of size-8. This would result in a waste of (4-2) + (4-3) + (8-5) = 6.
//
//
// Return the minimum total wasted space by choosing the box supplier optimally, or -1 if it is impossible to fit all the packages inside boxes. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: packages = [2,3,5], boxes = [[4,8],[2,8]]
// Output: 6
// Explanation: It is optimal to choose the first supplier, using two size-4 boxes and one size-8 box.
// The total waste is (4-2) + (4-3) + (8-5) = 6.
//
// Constraints:
// n == packages.length
// 	m == boxes.length
// 	1 <= n <= 105
// 	1 <= m <= 105
// 	1 <= packages[i] <= 105
// 	1 <= boxes[j].length <= 105
// 	1 <= boxes[j][k] <= 105
// 	sum(boxes[j].length) <= 105
// 	The elements in boxes[j] are distinct.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
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

int minWastedSpace(int* packages, int packagesSize, int** boxes, int boxesSize, int* boxesColSize) {
    const int MOD = 1000000007;
    /* Sort packages to facilitate binary search */
    qsort(packages, packagesSize, sizeof(int), cmpInt);

    long long minWaste = -1;

    for (int i = 0; i < boxesSize; ++i) {
        int *boxSizes = boxes[i];
        int boxCount = boxesColSize[i];
        /* Sort box sizes for this supplier */
        qsort(boxSizes, boxCount, sizeof(int), cmpInt);

        long long waste = 0;
        int pkgIdx = 0;

        for (int j = 0; j < boxCount && pkgIdx < packagesSize; ++j) {
            int boxSize = boxSizes[j];
            /* Find how many packages can fit in this box size */
            int left = pkgIdx, right = packagesSize - 1, fitIdx = pkgIdx - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (packages[mid] <= boxSize) {
                    fitIdx = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            /* Calculate waste for packages that fit in this box size */
            for (int k = pkgIdx; k <= fitIdx; ++k) {
                waste += (long long)(boxSize - packages[k]);
            }
            pkgIdx = fitIdx + 1;
        }

        if (pkgIdx == packagesSize) { /* All packages fitted */
            if (minWaste == -1 || waste < minWaste) {
                minWaste = waste;
            }
        }
    }

    return (minWaste == -1) ? -1 : (int)(minWaste % MOD);       
}
