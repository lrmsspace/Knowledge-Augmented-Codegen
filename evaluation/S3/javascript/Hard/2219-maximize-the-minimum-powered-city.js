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
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} stations
 * @param {number} r
 * @param {number} k
 * @return {number}
 */
var maxPower = function(stations, r, k) {
    const n = stations.length;
    const power = new Array(n).fill(0);

    // Calculate the initial power of each city
    for (let i = 0; i < n; i++) {
        const left = Math.max(0, i - r);
        const right = Math.min(n - 1, i + r);

        for (let j = left; j <= right; j++) {
            power[j] += stations[i];
        }
    }

    // Binary search for the maximum minimum power
    let low = 0;
    let high = Math.max(...power) + k; // The maximum possible power after adding k stations
    while (low < high) {
        const mid = Math.floor((low + high + 1) / 2);
        let neededStations = 0; 

        for (let i = 0; i < n; i++) {
            if (power[i] < mid) {
                neededStations += mid - power[i];
                power[i] = mid; // Update the power to mid for the next cities
            }
            if (neededStations > k) {
                break; // No need to continue if we already need more than k stations
            }
        }   
        if (neededStations <= k) {
            low = mid; // We can achieve at least mid power, try for a higher value
        } else {
            high = mid - 1; // We cannot achieve mid power, try for a lower value
        }
    }
    return low; 
    
};
