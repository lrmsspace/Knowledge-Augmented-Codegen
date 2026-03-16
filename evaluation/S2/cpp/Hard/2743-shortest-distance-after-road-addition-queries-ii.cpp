// Source: https://leetcode.com/problems/shortest-distance-after-road-addition-queries-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D integer array queries.
//
// There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.
//
// queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
//
// There are no two queries such that queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
//
// Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
//
// Example:
// Input: n = 5, queries = [[2,4],[0,2],[0,4]]
//
// Output: [3,2,1]
//
// Explanation: 
//
//
//
// After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
//
//
//
// After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
//
//
//
// After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.
//
// Constraints:
// 3 <= n <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= queries[i][0] < queries[i][1] < n
// 	1 < queries[i][1] - queries[i][0]
// 	There are no repeated roads among the queries.
// 	There are no two queries such that i != j and queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> answer;
        int shortestPath = n - 1; // Initial shortest path from city 0 to city n - 1

        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];

            // Calculate the new shortest path considering the newly added road
            int newShortestPath = min(shortestPath, (v - u) + (n - 1 - v));
            answer.push_back(newShortestPath);
            shortestPath = newShortestPath; // Update the shortest path for the next iteration
        }

        return answer;          
    }
};
