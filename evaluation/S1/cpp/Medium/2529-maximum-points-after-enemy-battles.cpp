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
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy) {
        // Max-heap to store energies of marked enemies
        priority_queue<int> markedEnemies;
        long long points = 0;
        int energy = currentEnergy;

        for (int enemy : enemyEnergies) {
            if (energy >= enemy) {
                // Defeat the enemy
                energy -= enemy;
                points++;
            } else if (!markedEnemies.empty() && markedEnemies.top() > enemy) {
                // Mark the strongest marked enemy to gain energy
                energy += markedEnemies.top();
                markedEnemies.pop();
                // Now defeat the current enemy
                energy -= enemy;
                points++;
            }
            // Mark the current enemy
            markedEnemies.push(enemy);
        }

        return points;          
    }
};
