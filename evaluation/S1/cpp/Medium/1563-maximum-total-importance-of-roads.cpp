// Source: https://leetcode.com/problems/maximum-total-importance-of-roads/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n denoting the number of cities in a country. The cities are numbered from 0 to n - 1.
//
// You are also given a 2D integer array roads where roads[i] = [ai, bi] denotes that there exists a bidirectional road connecting cities ai and bi.
//
// You need to assign each city with an integer value from 1 to n, where each value can only be used once. The importance of a road is then defined as the sum of the values of the two cities it connects.
//
// Return the maximum total importance of all roads possible after assigning the values optimally.
//
// Example:
// Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
// Output: 43
// Explanation: The figure above shows the country and the assigned values of [2,4,5,3,1].
// - The road (0,1) has an importance of 2 + 4 = 6.
// - The road (1,2) has an importance of 4 + 5 = 9.
// - The road (2,3) has an importance of 5 + 3 = 8.
// - The road (0,2) has an importance of 2 + 5 = 7.
// - The road (1,3) has an importance of 4 + 3 = 7.
// - The road (2,4) has an importance of 5 + 1 = 6.
// The total importance of all roads is 6 + 9 + 8 + 7 + 7 + 6 = 43.
// It can be shown that we cannot obtain a greater total importance than 43.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	1 <= roads.length <= 5 * 104
// 	roads[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no duplicate roads.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<int> degree(n, 0);
        for (const auto& road : roads) {
            degree[road[0]]++;
            degree[road[1]]++;
        }

        // Create a vector of pairs (degree, city_index)
        vector<pair<int, int>> deg_city;
        for (int i = 0; i < n; ++i) {
            deg_city.push_back({degree[i], i});
        }

        // Sort cities by degree in descending order
        sort(deg_city.rbegin(), deg_city.rend());

        // Assign importance values from n down to 1 based on sorted degrees
        vector<int> importance(n, 0);
        for (int i = 0; i < n; ++i) {
            importance[deg_city[i].second] = n - i;
        }

        // Calculate total importance of all roads
        long long total_importance = 0;
        for (const auto& road : roads) {
            total_importance += importance[road[0]] + importance[road[1]];
        }

        return total_importance;            
    }
};
