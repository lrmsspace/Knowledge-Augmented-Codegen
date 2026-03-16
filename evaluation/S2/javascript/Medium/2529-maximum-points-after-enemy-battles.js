// Source: https://leetcode.com/problems/maximum-points-after-enemy-battles/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array enemyEnergies denoting the energy values of various enemies.
//
// You are also given an integer currentEnergy denoting the amount of energy you have initially.
//
// You start with 0 points, and all the enemies are unmarked initially.
//
// You can perform either of the following operations zero or multiple times to gain points:
//
//
// 	Choose an unmarked enemy, i, such that currentEnergy >= enemyEnergies[i]. By choosing this option:
//
// 	
// 		You gain 1 point.
// 		Your energy is reduced by the enemy's energy, i.e. currentEnergy = currentEnergy - enemyEnergies[i].
// 	
// 	
// 	If you have at least 1 point, you can choose an unmarked enemy, i. By choosing this option:
// 	
// 		Your energy increases by the enemy's energy, i.e. currentEnergy = currentEnergy + enemyEnergies[i].
// 		The enemy i is marked.
// 	
// 	
//
//
// Return an integer denoting the maximum points you can get in the end by optimally performing operations.
//
// Example:
// Input: enemyEnergies = [3,2,2], currentEnergy = 2
//
// Output: 3
//
// Explanation:
//
// The following operations can be performed to get 3 points, which is the maximum:
//
//
// 	First operation on enemy 1: points increases by 1, and currentEnergy decreases by 2. So, points = 1, and currentEnergy = 0.
// 	Second operation on enemy 0: currentEnergy increases by 3, and enemy 0 is marked. So, points = 1, currentEnergy = 3, and marked enemies = [0].
// 	First operation on enemy 2: points increases by 1, and currentEnergy decreases by 2. So, points = 2, currentEnergy = 1, and marked enemies = [0].
// 	Second operation on enemy 2: currentEnergy increases by 2, and enemy 2 is marked. So, points = 2, currentEnergy = 3, and marked enemies = [0, 2].
// 	First operation on enemy 1: points increases by 1, and currentEnergy decreases by 2. So, points = 3, currentEnergy = 1, and marked enemies = [0, 2].
//
// Constraints:
// 1 <= enemyEnergies.length <= 105
// 	1 <= enemyEnergies[i] <= 109
// 	0 <= currentEnergy <= 109
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} enemyEnergies
 * @param {number} currentEnergy
 * @return {number}
 */
var maximumPoints = function(enemyEnergies, currentEnergy) {
    enemyEnergies.sort((a, b) => a - b);
    let points = 0;
    let left = 0;
    let right = enemyEnergies.length - 1;

    while (left <= right) {
        if (currentEnergy >= enemyEnergies[left]) {
            currentEnergy -= enemyEnergies[left];
            points++;
            left++;
        } else if (points > 0) {
            currentEnergy += enemyEnergies[right];
            points--;
            right--;
        } else {
            break;
        }
    }

    return points;
};
