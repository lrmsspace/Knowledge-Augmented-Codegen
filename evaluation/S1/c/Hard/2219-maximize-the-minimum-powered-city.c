// Source: https://leetcode.com/problems/maximize-the-minimum-powered-city/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array stations of length n, where stations[i] represents the number of power stations in the ith city.
//
// Each power station can provide power to every city in a fixed range. In other words, if the range is denoted by r, then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.
//
//
// 	Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
//
//
// The power of a city is the total number of power stations it is being provided power from.
//
// The government has sanctioned building k more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.
//
// Given the two integers r and k, return the maximum possible minimum power of a city, if the additional power stations are built optimally.
//
// Note that you can build the k power stations in multiple cities.
//
// Example:
// Input: stations = [1,2,4,5,0], r = 1, k = 2
// Output: 5
// Explanation: 
// One of the optimal ways is to install both the power stations at city 1. 
// So stations will become [1,4,4,5,0].
// - City 0 is provided by 1 + 4 = 5 power stations.
// - City 1 is provided by 1 + 4 + 4 = 9 power stations.
// - City 2 is provided by 4 + 4 + 5 = 13 power stations.
// - City 3 is provided by 5 + 4 = 9 power stations.
// - City 4 is provided by 5 + 0 = 5 power stations.
// So the minimum power of a city is 5.
// Since it is not possible to obtain a larger power, we return 5.
//
// Constraints:
// n == stations.length
// 	1 <= n <= 105
// 	0 <= stations[i] <= 105
// 	0 <= r <= n - 1
// 	0 <= k <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
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

long long maxPower(int* stations, int stationsSize, int r, int k) {
    long long left = 0, right = 0;
    for (int i = 0; i < stationsSize; ++i) {
        right += stations[i];
    }
    right += k; /* maximum possible power per city */

    /* Check if it's possible to achieve at least 'target' power per city */
    auto bool canAchieve(long long target) {
        long long *power = (long long*)calloc(stationsSize, sizeof(long long));
        if (!power) return false;

        long long addStations = 0;
        long long windowSum = 0;
        for (int i = 0; i < stationsSize; ++i) {
            if (i > r) windowSum -= power[i - r - 1];
            windowSum += stations[i];
            if (windowSum < target) {
                long long needed = target - windowSum;
                addStations += needed;
                if (addStations > k) {
                    free(power);
                    return false;
                }
                power[i] = needed;
                windowSum += needed;
            }
        }
        free(power);
        return true;
    }

    /* Binary search for the maximum minimum power */
    long long result = 0;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (canAchieve(mid)) {
            result = mid; /* mid is achievable, try for a larger value */
            left = mid + 1;
        } else {
            right = mid - 1; /* mid is not achievable, try smaller value */
        }
    }
    return result;      
}
