// Source: https://leetcode.com/problems/smallest-sufficient-team/   |   Difficulty: Hard
//
// Problem Description:
// In a project, you have a list of required skills req_skills, and a list of people. The ith person people[i] contains a list of skills that the person has.
//
// Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill. We can represent these teams by the index of each person.
//
//
// 	For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
//
//
// Return any sufficient team of the smallest possible size, represented by the index of each person. You may return the answer in any order.
//
// It is guaranteed an answer exists.
//
// Example:
// Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
// Output: [0,2]
//
// Constraints:
// 1 <= req_skills.length <= 16
// 	1 <= req_skills[i].length <= 16
// 	req_skills[i] consists of lowercase English letters.
// 	All the strings of req_skills are unique.
// 	1 <= people.length <= 60
// 	0 <= people[i].length <= 16
// 	1 <= people[i][j].length <= 16
// 	people[i][j] consists of lowercase English letters.
// 	All the strings of people[i] are unique.
// 	Every skill in people[i] is a skill in req_skills.
// 	It is guaranteed a sufficient team exists.
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] smallestSufficientTeam(String[] req_skills, List<List<String>> people) {
        int n = req_skills.length;
        int m = people.size();
        Map<String, Integer> skillIndex = new HashMap<>();
        for (int i = 0; i < n; i++) {
            skillIndex.put(req_skills[i], i);
        }

        int[] personSkills = new int[m];
        for (int i = 0; i < m; i++) {
            for (String skill : people.get(i)) {
                if (skillIndex.containsKey(skill)) {
                    personSkills[i] |= (1 << skillIndex.get(skill));
                }
            }
        }

        int totalSkills = 1 << n;
        int[] dp = new int[totalSkills];
        Arrays.fill(dp, Integer.MAX_VALUE / 2);
        dp[0] = 0;

        int[] parent = new int[totalSkills];
        int[] lastPerson = new int[totalSkills];

        for (int i = 0; i < m; i++) {
            int skillSet = personSkills[i];
            for (int mask = 0; mask < totalSkills; mask++) {
                int newMask = mask | skillSet;
                if (dp[newMask] > dp[mask] + 1) {
                    dp[newMask] = dp[mask] + 1;
                    parent[newMask] = mask;
                    lastPerson[newMask] = i;
                }
            }
        }

        List<Integer> result = new ArrayList<>();
        int mask = totalSkills - 1;
        while (mask != 0) {
            result.add(lastPerson[mask]);
            mask = parent[mask];
        }

        return result.stream().mapToInt(i -> i).toArray();          
    }
}
