// Source: https://leetcode.com/problems/closest-dessert-cost/   |   Difficulty: Medium
//
// Problem Description:
// You would like to make dessert and are preparing to buy the ingredients. You have n ice cream base flavors and m types of toppings to choose from. You must follow these rules when making your dessert:
//
//
// 	There must be exactly one ice cream base.
// 	You can add one or more types of topping or have no toppings at all.
// 	There are at most two of each type of topping.
//
//
// You are given three inputs:
//
//
// 	baseCosts, an integer array of length n, where each baseCosts[i] represents the price of the ith ice cream base flavor.
// 	toppingCosts, an integer array of length m, where each toppingCosts[i] is the price of one of the ith topping.
// 	target, an integer representing your target price for dessert.
//
//
// You want to make a dessert with a total cost as close to target as possible.
//
// Return the closest possible cost of the dessert to target. If there are multiple, return the lower one.
//
// Example:
// Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
// Output: 10
// Explanation: Consider the following combination (all 0-indexed):
// - Choose base 1: cost 7
// - Take 1 of topping 0: cost 1 x 3 = 3
// - Take 0 of topping 1: cost 0 x 4 = 0
// Total: 7 + 3 + 0 = 10.
//
// Constraints:
// n == baseCosts.length
// 	m == toppingCosts.length
// 	1 <= n, m <= 10
// 	1 <= baseCosts[i], toppingCosts[i] <= 104
// 	1 <= target <= 104
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Backtracking Algorithm (graph, backtracking, recursion, dfs)
//   • When to use: Used when exploring multiple possibilities to find a solution incrementally, often involving undoing choices if they lead to a dead end.
//   • Idea: Backtracking is a problem-solving technique that incrementally builds a solution by trying options and undoing them upon reaching a dead end. It typically explores a search space in a depth-first manner, often resulting in exponential time complexity.
//   • Invariants: The current partial solution is valid up to the current decision point.; All choices made to reach the current state can be systematically undone.
//   • Tips: Define clear base cases for recursive termination.; Identify decision points and available choices at each step.
//   • Pitfalls: Forgetting to undo changes (backtrack) after exploring a path.; Incorrectly defining base cases, leading to infinite recursion or wrong results.
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int closest = baseCosts[0];
        for (int bcost : baseCosts) {
            closest = abs(bcost - target) < abs(closest - target) ?
                      bcost :
                      (abs(bcost - target) == abs(closest - target) ?
                       min(bcost, closest) :
                       closest);
            // Try all topping combinations via bitmask
            int m = toppingCosts.size();
            int totalComb = 1 << (2 * m); // each topping can be used 0, 1, or 2 times
            for (int mask = 0; mask < totalComb; ++mask) {
                int tcost = 0;
                for (int i = 0; i < m; ++i) {
                    int count = (mask >> (2 * i)) & 3; // extract 2 bits for topping i
                    tcost += count * toppingCosts[i];
                }
                int totalCost = bcost + tcost;
                closest = abs(totalCost - target) < abs(closest - target) ?
                          totalCost :
                          (abs(totalCost - target) == abs(closest - target) ?
                           min(totalCost, closest) :
                           closest);
            }
        }
        return closest;         
    }
};
