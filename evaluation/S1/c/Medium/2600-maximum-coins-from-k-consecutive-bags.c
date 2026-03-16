// Source: https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/   |   Difficulty: Medium
//
// Problem Description:
// There are an infinite amount of bags on a number line, one bag for each coordinate. Some of these bags contain coins.
//
// You are given a 2D array coins, where coins[i] = [li, ri, ci] denotes that every bag from li to ri contains ci coins.
//
// The segments that coins contain are non-overlapping.
//
// You are also given an integer k.
//
// Return the maximum amount of coins you can obtain by collecting k consecutive bags.
//
// Example:
// Input: coins = [[8,10,1],[1,3,2],[5,6,4]], k = 4
//
// Output: 10
//
// Explanation:
//
// Selecting bags at positions [3, 4, 5, 6] gives the maximum number of coins: 2 + 0 + 4 + 4 = 10.
//
// Constraints:
// 1 <= coins.length <= 105
// 	1 <= k <= 109
// 	coins[i] == [li, ri, ci]
// 	1 <= li <= ri <= 109
// 	1 <= ci <= 1000
// 	The given segments are non-overlapping.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maximumCoins(int** coins, int coinsSize, int* coinsColSize, int k) {
    // Create an array to hold the events (start and end of segments)
    typedef struct {
        long long position;
        int type; // 1 for start, -1 for end
        int coins;
    } Event;

    Event* events = (Event*)malloc(sizeof(Event) * coinsSize * 2);
    int eventCount = 0;

    for (int i = 0; i < coinsSize; i++) {
        events[eventCount++] = (Event){coins[i][0], 1, coins[i][2]};
        events[eventCount++] = (Event){coins[i][1] + 1, -1, coins[i][2]};
    }

    // Sort events by position
    int compare(const void* a, const void* b) {
        Event* ea = (Event*)a;
        Event* eb = (Event*)b;
        if (ea->position == eb->position) {
            return ea->type - eb->type; // End events before start events
        }
        return (ea->position < eb->position) ? -1 : 1;
    }
    qsort(events, eventCount, sizeof(Event), compare);

    // Sweep line to calculate prefix sums
    long long* prefixSums = (long long*)malloc(sizeof(long long) * (eventCount + 1));
    long long* positions = (long long*)malloc(sizeof(long long) * (eventCount + 1));
    long long currentCoins = 0;
    long long lastPosition = 0;
    int idx = 0;

    for (int i = 0; i < eventCount; i++) {
        if (events[i].position != lastPosition) {
            positions[idx] = lastPosition;
            prefixSums[idx] = currentCoins;
            idx++;
            lastPosition = events[i].position;
        }
        currentCoins += events[i].type * events[i].coins;
    }
    // Add the last position
    positions[idx] = lastPosition;
    prefixSums[idx] = currentCoins;
    idx++;

    // Calculate the maximum coins in any k-length segment
    long long maxCoins = 0;
    for (int i = 0; i < idx; i++) {
        long long startPos = positions[i];
        long long endPos = startPos + k;
        // Binary search to find the end position   
        int left = 0, right = idx - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (positions[mid] < endPos) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        long long totalCoins = 0;
        for (int j = i; j < left; j++) {
            long long segmentStart = positions[j];
            long long segmentEnd = (j + 1 < idx) ? positions[j + 1] : endPos;
            if (segmentEnd > endPos) {
                segmentEnd = endPos;
            }
            totalCoins += prefixSums[j] * (segmentEnd - segmentStart);
        }
        if (totalCoins > maxCoins) {
            maxCoins = totalCoins;
        }

}
    free(events);
    free(prefixSums);
    free(positions);
    return maxCoins;
}