// Source: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
//
// Return the minimum possible absolute difference.
//
// Example:
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
//
// Constraints:
// 1 <= n <= 15
// 	nums.length == 2 * n
// 	-107 <= nums[i] <= 107
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumDifference(int* nums, int numsSize) {
    int n = numsSize / 2;
    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum += nums[i];
    }

    int half = totalSum / 2;
    int size = 1 << n;
    int *leftSums[ n + 1 ];
    int *rightSums[ n + 1 ];
    int leftSizes[ n + 1 ];
    int rightSizes[ n + 1 ];
    memset(leftSizes, 0, sizeof(leftSizes));
    memset(rightSizes, 0, sizeof(rightSizes));

    for (int mask = 0; mask < size; ++mask) {
        int sumLeft = 0, sumRight = 0, countLeft = 0, countRight = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sumLeft += nums[i];
                countLeft++;
            } else {
                sumRight += nums[i + n];
                countRight++;
            }
        }
        if (!leftSums[countLeft]) {
            leftSums[countLeft] = (int*)malloc(sizeof(int) * size);
        }
        leftSums[countLeft][leftSizes[countLeft]++] = sumLeft;
        if (!rightSums[countRight]) {
            rightSums[countRight] = (int*)malloc(sizeof(int) * size);
        }
        rightSums[countRight][rightSizes[countRight]++] = sumRight;
    }

    for (int i = 0; i <= n; ++i) {
        qsort(rightSums[i], rightSizes[i], sizeof(int), cmpInt);
    }

    int minDiff = totalSum;
    for (int count = 0; count <= n; ++count) {
        for (int i = 0; i < leftSizes[count]; ++i) {
            int leftSum = leftSums[count][i];
            int target = half - leftSum;
            int *rightArray = rightSums[n - count];
            int rightSize = rightSizes[n - count];

            // Binary search in rightArray
            int low = 0, high = rightSize - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (rightArray[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            // Check the closest sums
            if (low < rightSize) {
                int currentSum = leftSum + rightArray[low];
                int currentDiff = abs(totalSum - 2 * currentSum);
                if (currentDiff < minDiff) {
                    minDiff = currentDiff;
                }
            }
            if (low > 0) {
                int currentSum = leftSum + rightArray[low - 1];
                int currentDiff = abs(totalSum - 2 * currentSum);
                if (currentDiff < minDiff) {
                    minDiff = currentDiff;
                }
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        free(leftSums[i]);
        free(rightSums[i]);
    }
    return minDiff;
}
