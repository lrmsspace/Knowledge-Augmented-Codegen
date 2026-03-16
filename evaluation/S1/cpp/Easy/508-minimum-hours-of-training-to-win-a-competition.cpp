// Source: https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/   |   Difficulty: Easy
//
// Problem Description:
// You are entering a competition, and are given two positive integers initialEnergy and initialExperience denoting your initial energy and initial experience respectively.
//
// You are also given two 0-indexed integer arrays energy and experience, both of length n.
//
// You will face n opponents in order. The energy and experience of the ith opponent is denoted by energy[i] and experience[i] respectively. When you face an opponent, you need to have both strictly greater experience and energy to defeat them and move to the next opponent if available.
//
// Defeating the ith opponent increases your experience by experience[i], but decreases your energy by energy[i].
//
// Before starting the competition, you can train for some number of hours. After each hour of training, you can either choose to increase your initial experience by one, or increase your initial energy by one.
//
// Return the minimum number of training hours required to defeat all n opponents.
//
// Example:
// Input: initialEnergy = 5, initialExperience = 3, energy = [1,4,3,2], experience = [2,6,3,1]
// Output: 8
// Explanation: You can increase your energy to 11 after 6 hours of training, and your experience to 5 after 2 hours of training.
// You face the opponents in the following order:
// - You have more energy and experience than the 0th opponent so you win.
//   Your energy becomes 11 - 1 = 10, and your experience becomes 5 + 2 = 7.
// - You have more energy and experience than the 1st opponent so you win.
//   Your energy becomes 10 - 4 = 6, and your experience becomes 7 + 6 = 13.
// - You have more energy and experience than the 2nd opponent so you win.
//   Your energy becomes 6 - 3 = 3, and your experience becomes 13 + 3 = 16.
// - You have more energy and experience than the 3rd opponent so you win.
//   Your energy becomes 3 - 2 = 1, and your experience becomes 16 + 1 = 17.
// You did a total of 6 + 2 = 8 hours of training before the competition, so we return 8.
// It can be proven that no smaller answer exists.
//
// Constraints:
// n == energy.length == experience.length
// 	1 <= n <= 100
// 	1 <= initialEnergy, initialExperience, energy[i], experience[i] <= 100
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int>& energy, vector<int>& experience) {
        int trainingHours = 0;
        int currentEnergy = initialEnergy;
        int currentExperience = initialExperience;

        for (size_t i = 0; i < energy.size(); ++i) {
            // Check and train for energy if needed
            if (currentEnergy <= energy[i]) {
                trainingHours += (energy[i] - currentEnergy + 1);
                currentEnergy = energy[i] + 1; // Increase energy to just above opponent's energy
            }
            currentEnergy -= energy[i]; // Decrease energy after the match

            // Check and train for experience if needed
            if (currentExperience <= experience[i]) {
                trainingHours += (experience[i] - currentExperience + 1);
                currentExperience = experience[i] + 1; // Increase experience to just above opponent's experience
            }
            currentExperience += experience[i]; // Increase experience after the match
        }

        return trainingHours;           
    }
};
