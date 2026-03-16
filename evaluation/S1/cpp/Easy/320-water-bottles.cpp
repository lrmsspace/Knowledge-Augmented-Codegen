// Source: https://leetcode.com/problems/water-bottles/   |   Difficulty: Easy
//
// Problem Description:
// There are numBottles water bottles that are initially full of water. You can exchange numExchange empty water bottles from the market with one full water bottle.
//
// The operation of drinking a full water bottle turns it into an empty bottle.
//
// Given the two integers numBottles and numExchange, return the maximum number of water bottles you can drink.
//
// Example:
// Input: numBottles = 9, numExchange = 3
// Output: 13
// Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
// Number of water bottles you can drink: 9 + 3 + 1 = 13.
//
// Constraints:
// 1 <= numBottles <= 100
// 	2 <= numExchange <= 100
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Maximum flow - Push-relabel algorithm (graph, number, simulation)
//   • When to use: Use when computing the maximum flow in a network, especially for dense graphs where its O(V^2 E) complexity can be competitive. It's an alternative to augmenting path algorithms.
//   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from vertices and relabeling them until a valid flow is achieved. It typically runs in O(V^2 E) time.
//   • Invariants: For any edge (u, v) in the residual graph with positive capacity, h(u) <= h(v) + 1.; Excess flow at the source (s) is always non-negative, and at the sink (t) is always non-positive.
//   • Tips: Initialize the graph with a valid preflow and height function.; Prioritize pushing excess from vertices with the highest labels.
//   • Pitfalls: Incorrectly updating residual capacities after a push operation.; Violating the height function validity condition (h(u) <= h(v) + 1).
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
//   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
//   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
//   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int totalDrunk = numBottles;
        int emptyBottles = numBottles;
        
        while (emptyBottles >= numExchange) {
            int newBottles = emptyBottles / numExchange;
            totalDrunk += newBottles;
            emptyBottles = emptyBottles % numExchange + newBottles;
        }
        
        return totalDrunk;          
    }
};
