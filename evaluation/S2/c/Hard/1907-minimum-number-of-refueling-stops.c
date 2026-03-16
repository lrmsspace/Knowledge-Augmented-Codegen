// Source: https://leetcode.com/problems/minimum-number-of-refueling-stops/   |   Difficulty: Hard
//
// Problem Description:
// A car travels from a starting position to a destination which is target miles east of the starting position.
//
// There are gas stations along the way. The gas stations are represented as an array stations where stations[i] = [positioni, fueli] indicates that the ith gas station is positioni miles east of the starting position and has fueli liters of gas.
//
// The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it. It uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.
//
// Return the minimum number of refueling stops the car must make in order to reach its destination. If it cannot reach the destination, return -1.
//
// Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there. If the car reaches the destination with 0 fuel left, it is still considered to have arrived.
//
// Example:
// Input: target = 1, startFuel = 1, stations = []
// Output: 0
// Explanation: We can reach the target without refueling.
//
// Constraints:
// 1 <= target, startFuel <= 109
// 	0 <= stations.length <= 500
// 	1 <= positioni < positioni+1 < target
// 	1 <= fueli < 109
//
// Helpful references (internal KB):
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minRefuelStops(int target, int startFuel, int** stations, int stationsSize, int* stationsColSize) {
    // The maximum number of refueling stops is at most the number of stations, so we can use a dynamic programming approach where dp[i] represents the farthest distance that can be reached with i refueling stops.
    long long dp[stationsSize + 1];
    for (int i = 0; i <= stationsSize; i++) {
        dp[i] = 0; // Initialize all distances to 0
    }
    dp[0] = startFuel; // With 0 stops, we can reach as far as startFuel

    for (int i = 0; i < stationsSize; i++) {
        int position = stations[i][0];
        int fuel = stations[i][1];
        // We need to check if we can reach this station with any of the previous stops
        for (int j = i; j >= 0; j--) {
            if (dp[j] >= position) { // If we can reach this station with j stops
                if (dp[j] + fuel > dp[j + 1]) { // If refueling here gives us a farther distance
                    dp[j + 1] = dp[j] + fuel; // Update the distance for j+1 stops
                }
            } else {
                break; // If we can't reach this station with j stops, we won't be able to with more stops either
            }
        }
    }

    // Now we check the dp array to find the minimum number of stops needed to reach the target
    for (int i = 0; i <= stationsSize; i++) {
        if (dp[i] >= target) {
            return i; // Return the minimum number of stops needed
        }
    }
    
    return -1; // If we can't reach the target with any number of stops, return -1      
}
