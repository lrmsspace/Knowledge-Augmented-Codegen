// Source: https://leetcode.com/problems/remove-methods-from-project/   |   Difficulty: Medium
//
// Problem Description:
// You are maintaining a project that has n methods numbered from 0 to n - 1.
//
// You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.
//
// There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.
//
// A group of methods can only be removed if no method outside the group invokes any methods within it.
//
// Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.
//
// Example:
// Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
//
// Output: [0,1,2,3]
//
// Explanation:
//
//
//
// Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= k <= n - 1
// 	0 <= invocations.length <= 2 * 105
// 	invocations[i] == [ai, bi]
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	invocations[i] != invocations[j]
//

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        vector<vector<int>> reverseGraph(n);
        for (const auto& inv : invocations) {
            graph[inv[0]].push_back(inv[1]);
            reverseGraph[inv[1]].push_back(inv[0]);
        }

        vector<bool> suspicious(n, false);
        function<void(int)> dfs = [&](int node) {
            if (suspicious[node]) return;
            suspicious[node] = true;
            for (int neighbor : graph[node]) {
                dfs(neighbor);
            }
        };
        dfs(k);

        for (int i = 0; i < n; ++i) {
            if (!suspicious[i]) {
                for (int neighbor : graph[i]) {
                    if (suspicious[neighbor]) {
                        return vector<int>(n); // Return empty array
                    }
                }
            }
        }

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (!suspicious[i]) {
                result.push_back(i);
            }
        }
        return result;          
    }
};
