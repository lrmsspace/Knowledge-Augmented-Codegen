// Source: https://leetcode.com/problems/evaluate-division/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
//
// You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.
//
// Return the answers to all queries. If a single answer cannot be determined, return -1.0.
//
// Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.
//
// Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.
//
// Example:
// Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
// Explanation: 
// Given: a / b = 2.0, b / c = 3.0
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
// return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
// note: x is undefined => -1.0
//
// Constraints:
// 1 <= equations.length <= 20
// 	equations[i].length == 2
// 	1 <= Ai.length, Bi.length <= 5
// 	values.length == equations.length
// 	0.0 < values[i] <= 20.0
// 	1 <= queries.length <= 20
// 	queries[i].length == 2
// 	1 <= Cj.length, Dj.length <= 5
// 	Ai, Bi, Cj, Dj consist of lower case English letters and digits.
//

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, vector<pair<string, double>>> graph;
        for (int i = 0; i < equations.size(); ++i) {
            const auto& eq = equations[i];
            graph[eq[0]].emplace_back(eq[1], values[i]);
            graph[eq[1]].emplace_back(eq[0], 1.0 / values[i]);
        }

        vector<double> results;
        for (const auto& query : queries) {
            const string& start = query[0];
            const string& end = query[1];
            if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
                results.push_back(-1.0);
                continue;
            }
            if (start == end) {
                results.push_back(1.0);
                continue;
            }

            unordered_set<string> visited;
            double result = -1.0;
            dfs(graph, start, end, 1.0, visited, result);
            results.push_back(result);
        }
        return results;         
    }
};
