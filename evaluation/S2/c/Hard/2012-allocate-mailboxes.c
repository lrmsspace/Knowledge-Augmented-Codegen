// Source: https://leetcode.com/problems/allocate-mailboxes/   |   Difficulty: Hard
//
// Problem Description:
// Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.
//
// Return the minimum total distance between each house and its nearest mailbox.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: houses = [1,4,8,10,20], k = 3
// Output: 5
// Explanation: Allocate mailboxes in position 3, 9 and 20.
// Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
//
// Constraints:
// 1 <= k <= houses.length <= 100
// 	1 <= houses[i] <= 104
// 	All the integers of houses are unique.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minDistance(int* houses, int housesSize, int k) {
    // Sort the houses to ensure they are in order.
    for (int i = 0; i < housesSize - 1; i++) {
        for (int j = 0; j < housesSize - i - 1; j++) {
            if (houses[j] > houses[j + 1]) {
                int temp = houses[j];
                houses[j] = houses[j + 1];
                houses[j + 1] = temp;
            }
        }
    }

    // Create a dp array to store the minimum distance for subproblems.
    int dp[housesSize][k + 1];
    
    // Base case: When k = 1, the best we can do is place one mailbox at the median house.
    for (int i = 0; i < housesSize; i++) {
        int median = houses[i / 2];
        dp[i][1] = 0;
        for (int j = 0; j <= i; j++) {
            dp[i][1] += abs(houses[j] - median);
        }
    }

    // Fill the dp array using the recurrence relation.
    for (int j = 2; j <= k; j++) {
        for (int i = j - 1; i < housesSize; i++) {
            dp[i][j] = INT_MAX;
            for (int m = j - 2; m < i; m++) {
                int median = houses[(m + 1 + i) / 2];
                int cost = dp[m][j - 1];
                for (int n = m + 1; n <= i; n++) {
                    cost += abs(houses[n] - median);
                }
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[housesSize - 1][k];       
}
