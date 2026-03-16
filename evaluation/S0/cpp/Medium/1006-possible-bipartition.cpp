// Source: https://leetcode.com/problems/possible-bipartition/   |   Difficulty: Medium
//
// Problem Description:
// We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.
//
// Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
//
// Example:
// Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
// Explanation: The first group has [1,4], and the second group has [2,3].
//
// Constraints:
// 1 <= n <= 2000
// 	0 <= dislikes.length <= 104
// 	dislikes[i].length == 2
// 	1 <= ai < bi <= n
// 	All the pairs of dislikes are unique.
//

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : dislikes) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> color(n + 1, 0); // 0: uncolored, 1: color A, -1: color B

        function<bool(int, int)> dfs = [&](int node, int c) {
            color[node] = c;
            for (int neighbor : graph[node]) {
                if (color[neighbor] == 0) {
                    if (!dfs(neighbor, -c)) return false;
                } else if (color[neighbor] == c) {
                    return false;
                }
            }
            return true;
        };

        for (int i = 1; i <= n; ++i) {
            if (color[i] == 0) {
                if (!dfs(i, 1)) return false;
            }
        }

        return true;            
    }
};
