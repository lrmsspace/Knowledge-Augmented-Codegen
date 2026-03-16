// Source: https://leetcode.com/problems/minimum-time-to-finish-the-race/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array tires where tires[i] = [fi, ri] indicates that the ith tire can finish its xth successive lap in fi * ri(x-1) seconds.
//
//
// 	For example, if fi = 3 and ri = 2, then the tire would finish its 1st lap in 3 seconds, its 2nd lap in 3 * 2 = 6 seconds, its 3rd lap in 3 * 22 = 12 seconds, etc.
//
//
// You are also given an integer changeTime and an integer numLaps.
//
// The race consists of numLaps laps and you may start the race with any tire. You have an unlimited supply of each tire and after every lap, you may change to any given tire (including the current tire type) if you wait changeTime seconds.
//
// Return the minimum time to finish the race.
//
// Example:
// Input: tires = [[2,3],[3,4]], changeTime = 5, numLaps = 4
// Output: 21
// Explanation: 
// Lap 1: Start with tire 0 and finish the lap in 2 seconds.
// Lap 2: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Lap 3: Change tires to a new tire 0 for 5 seconds and then finish the lap in another 2 seconds.
// Lap 4: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Total time = 2 + 6 + 5 + 2 + 6 = 21 seconds.
// The minimum time to complete the race is 21 seconds.
//
// Constraints:
// 1 <= tires.length <= 105
// 	tires[i].length == 2
// 	1 <= fi, changeTime <= 105
// 	2 <= ri <= 105
// 	1 <= numLaps <= 1000
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
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

int minimumFinishTime(int** tires, int tiresSize, int* tiresColSize, int changeTime, int numLaps) {
    /* Precompute minimum time to finish k laps without changing tires */
    const int MAX_LAPS = 20; /* beyond this changing is always better */
    int minTime[MAX_LAPS + 1];
    for (int i = 0; i <= MAX_LAPS; i++) minTime[i] = 1e9;
    for (int i = 0; i < tiresSize; i++) {
        long long time = 0;
        long long f = tires[i][0];
        long long r = tires[i][1];
        for (int lap = 1; lap <= MAX_LAPS; lap++) {
            time += f;
            if (time > 1e9) break; /* no need to continue, too large */
            if (time < minTime[lap]) minTime[lap] = (int)time;
            f *= r;
        }
    }
    /* DP to compute minimum time to finish numLaps */
    int dp[numLaps + 1];
    dp[0] = 0;
    for (int lap = 1; lap <= numLaps; lap++) {
        dp[lap] = 1e9;
        for (int k = 1; k <= MAX_LAPS && k <= lap; k++) {
            int candidate = dp[lap - k] + minTime[k];
            if (lap - k > 0) candidate += changeTime;
            if (candidate < dp[lap]) dp[lap] = candidate;
        }
    }
    return dp[numLaps];     
}
