// Source: https://leetcode.com/problems/total-distance-traveled/   |   Difficulty: Easy
//
// Problem Description:
// A truck has two fuel tanks. You are given two integers, mainTank representing the fuel present in the main tank in liters and additionalTank representing the fuel present in the additional tank in liters.
//
// The truck has a mileage of 10 km per liter. Whenever 5 liters of fuel get used up in the main tank, if the additional tank has at least 1 liters of fuel, 1 liters of fuel will be transferred from the additional tank to the main tank.
//
// Return the maximum distance which can be traveled.
//
// Note: Injection from the additional tank is not continuous. It happens suddenly and immediately for every 5 liters consumed.
//
// Example:
// Input: mainTank = 5, additionalTank = 10
// Output: 60
// Explanation: 
// After spending 5 litre of fuel, fuel remaining is (5 - 5 + 1) = 1 litre and distance traveled is 50km.
// After spending another 1 litre of fuel, no fuel gets injected in the main tank and the main tank becomes empty.
// Total distance traveled is 60km.
//
// Constraints:
// 1 <= mainTank, additionalTank <= 100
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Maximum flow - Push-relabel algorithm (graph, queue, simulation)
//   • When to use: Used for finding the maximum flow in a flow network. It is particularly efficient for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
//   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes when flow cannot be pushed. It typically achieves a time complexity of O(V^2 * E) or O(V^3) with specific implementations.
//   • Invariants: For any edge (u, v) with positive residual capacity, h(u) <= h(v) + 1.; The source s always has h(s) = |V| and the sink t always has h(t) = 0.
//   • Tips: Initialize preflow by saturating edges from the source.; Initialize source height to |V| and others to 0.
//   • Pitfalls: Incorrectly handling residual capacities.; Not maintaining the height invariant during pushes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} mainTank
 * @param {number} additionalTank
 * @return {number}
 */
var distanceTraveled = function(mainTank, additionalTank) {
    let distance = 0;       
    while (mainTank > 0) {
        if (mainTank >= 5 && additionalTank > 0) {
            distance += 50; // 5 liters * 10 km/liter
            mainTank -= 5;
            mainTank += 1; // transfer 1 liter from additional tank
            additionalTank -= 1;
        } else {
            distance += mainTank * 10; // remaining fuel in main tank
            mainTank = 0; // main tank is now empty
        }
    }
    return distance; 
};
