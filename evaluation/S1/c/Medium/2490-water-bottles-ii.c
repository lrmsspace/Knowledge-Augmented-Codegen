// Source: https://leetcode.com/problems/water-bottles-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers numBottles and numExchange.
//
// numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:
//
//
// 	Drink any number of full water bottles turning them into empty bottles.
// 	Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
//
//
// Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.
//
// Return the maximum number of water bottles you can drink.
//
// Example:
// Input: numBottles = 13, numExchange = 6
// Output: 15
// Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.
//
// Constraints:
// 1 <= numBottles <= 100 
// 	1 <= numExchange <= 100
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
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxBottlesDrunk(int numBottles, int numExchange) {
    int totalDrunk = 0;
    int emptyBottles = 0;
    int exchangeRate = numExchange;

    while (numBottles > 0) {
        // Drink all full bottles
        totalDrunk += numBottles;
        emptyBottles += numBottles;
        numBottles = 0;

        // Exchange empty bottles for full ones
        while (emptyBottles >= exchangeRate) {
            int newFullBottles = emptyBottles / exchangeRate;
            numBottles += newFullBottles;
            emptyBottles -= newFullBottles * exchangeRate;
            exchangeRate++; // Increase the exchange rate after each successful exchange
        }
    }

    return totalDrunk;      
}
