// Source: https://leetcode.com/problems/minimum-speed-to-arrive-on-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given a floating-point number hour, representing the amount of time you have to reach the office. To commute to the office, you must take n trains in sequential order. You are also given an integer array dist of length n, where dist[i] describes the distance (in kilometers) of the ith train ride.
//
// Each train can only depart at an integer hour, so you may need to wait in between each train ride.
//
//
// 	For example, if the 1st train ride takes 1.5 hours, you must wait for an additional 0.5 hours before you can depart on the 2nd train ride at the 2 hour mark.
//
//
// Return the minimum positive integer speed (in kilometers per hour) that all the trains must travel at for you to reach the office on time, or -1 if it is impossible to be on time.
//
// Tests are generated such that the answer will not exceed 107 and hour will have at most two digits after the decimal point.
//
// Example:
// Input: dist = [1,3,2], hour = 6
// Output: 1
// Explanation: At speed 1:
// - The first train ride takes 1/1 = 1 hour.
// - Since we are already at an integer hour, we depart immediately at the 1 hour mark. The second train takes 3/1 = 3 hours.
// - Since we are already at an integer hour, we depart immediately at the 4 hour mark. The third train takes 2/1 = 2 hours.
// - You will arrive at exactly the 6 hour mark.
//
// Constraints:
// n == dist.length
// 	1 <= n <= 105
// 	1 <= dist[i] <= 105
// 	1 <= hour <= 109
// 	There will be at most two digits after the decimal point in hour.
//
// Helpful references (internal KB):
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
// - Continued fractions (number, array, enumeration)
//   • When to use: Use when representing real numbers as a sequence of integers for rational approximation, or when analyzing properties of irrational numbers. It's also useful for solving certain Diophantine equations and Pell's equation.
//   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, which is then represented in the same way. This process generates a sequence of integers, and its complexity depends on the desired precision or the number's nature.
//   • Invariants: The current integer term `a_i` is `floor(x_i)`, where `x_i` is the current real value being expanded.; The next real value `x_{i+1}` is `1 / (x_i - a_i)` if `x_i - a_i` is non-zero.
//   • Tips: Understand the recursive definition of continued fractions.; The Euclidean algorithm forms the basis for computing finite continued fractions.
//   • Pitfalls: Floating-point precision issues can severely limit accuracy for irrational numbers.; Misinterpreting convergents as exact values instead of approximations.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        if (hour <= n - 1) {
            return -1; // Not enough time to catch all trains
        }

        int left = 1, right = 10000000; // Speed range based on problem constraints
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            double totalTime = 0.0;

            for (int i = 0; i < n; ++i) {
                totalTime += (double)dist[i] / mid;
                if (totalTime > hour) {
                    break; // No need to continue if already over time
                }
            }

            if (totalTime <= hour) {
                result = mid; // Found a valid speed, try for a smaller one
                right = mid - 1;
            } else {
                left = mid + 1; // Need a faster speed
            }
        }

        return result;          
    }
};
