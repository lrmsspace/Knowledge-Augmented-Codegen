// Source: https://leetcode.com/problems/maximum-ice-cream-bars/   |   Difficulty: Medium
//
// Problem Description:
// It is a sweltering summer day, and a boy wants to buy some ice cream bars.
//
// At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 
//
// Note: The boy can buy the ice cream bars in any order.
//
// Return the maximum number of ice cream bars the boy can buy with coins coins.
//
// You must solve the problem by counting sort.
//
// Example:
// Input: costs = [1,3,2,4,1], coins = 7
// Output: 4
// Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
//
// Constraints:
// costs.length == n
// 	1 <= n <= 105
// 	1 <= costs[i] <= 105
// 	1 <= coins <= 108
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
//   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
//   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
//   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
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

int maxIceCream(int* costs, int costsSize, int coins) {
    int maxCost = 100000; // Given constraint: 1 <= costs[i] <= 10^5
    int count[maxCost + 1];
    for (int i = 0; i <= maxCost; i++) {
        count[i] = 0;
    }

    // Counting sort: Count occurrences of each cost
    for (int i = 0; i < costsSize; i++) {
        count[costs[i]]++;
    }

    int totalBars = 0;
    // Iterate through possible costs from lowest to highest
    for (int cost = 1; cost <= maxCost; cost++) {
        if (count[cost] == 0) {
            continue; // No ice cream bars at this cost
        }

        // Determine how many bars can be bought at this cost
        int affordableBars = coins / cost;
        if (affordableBars == 0) {
            break; // Cannot afford any more bars
        }

        int barsToBuy = (count[cost] < affordableBars) ? count[cost] : affordableBars;
        totalBars += barsToBuy;
        coins -= barsToBuy * cost;

        if (coins <= 0) {
            break; // No more coins left
        }
    }

    return totalBars;       
}
