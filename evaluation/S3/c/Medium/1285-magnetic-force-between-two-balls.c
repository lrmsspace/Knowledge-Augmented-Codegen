// Source: https://leetcode.com/problems/magnetic-force-between-two-balls/   |   Difficulty: Medium
//
// Problem Description:
// In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.
//
// Rick stated that magnetic force between two different balls at positions x and y is |x - y|.
//
// Given the integer array position and the integer m. Return the required force.
//
// Example:
// Input: position = [1,2,3,4,7], m = 3
// Output: 3
// Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.
//
// Constraints:
// n == position.length
// 	2 <= n <= 105
// 	1 <= position[i] <= 109
// 	All integers in position are distinct.
// 	2 <= m <= position.length
//
// Helpful references (internal KB):
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxDistance(int* position, int positionSize, int m) {
    // Sort the positions of the baskets to facilitate binary search and distance calculations
    qsort(position, positionSize, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // Define a helper function to check if it's possible to place m balls with at least 'distance' apart
    int canPlaceBalls(int distance) {
        int count = 1; // Start placing the first ball in the first basket
        int lastPosition = position[0]; // Position of the last placed ball

        for (int i = 1; i < positionSize; i++) {
            if (position[i] - lastPosition >= distance) {
                count++; // Place another ball
                lastPosition = position[i]; // Update the last placed ball's position
                if (count == m) {
                    return 1; // Successfully placed all m balls
                }
            }
        }
        return 0; // Not possible to place all m balls with this distance
    }

    // Binary search for the maximum minimum distance
    int left = 1; // Minimum possible distance
    int right = position[positionSize - 1] - position[0]; // Maximum possible distance

    while (left < right) {
        int mid = left + (right - left + 1) / 2; // Midpoint for binary search

        if (canPlaceBalls(mid)) {
            left = mid; // Try for a larger distance
        } else {
            right = mid - 1; // Try for a smaller distance
        }
    }

    return left; // The largest minimum distance found      
}
