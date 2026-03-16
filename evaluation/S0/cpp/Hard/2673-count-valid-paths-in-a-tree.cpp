// Source: https://leetcode.com/problems/count-valid-paths-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Return the number of valid paths in the tree.
//
// A path (a, b) is valid if there exists exactly one prime number among the node labels in the path from a to b.
//
// Note that:
//
//
// 	The path (a, b) is a sequence of distinct nodes starting with node a and ending with node b such that every two adjacent nodes in the sequence share an edge in the tree.
// 	Path (a, b) and path (b, a) are considered the same and counted only once.
//
// Example:
// Input: n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
// Output: 4
// Explanation: The pairs with exactly one prime number on the path between them are: 
// - (1, 2) since the path from 1 to 2 contains prime number 2. 
// - (1, 3) since the path from 1 to 3 contains prime number 3.
// - (1, 4) since the path from 1 to 4 contains prime number 2.
// - (2, 4) since the path from 2 to 4 contains prime number 2.
// It can be shown that there are only 4 valid paths.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	The input is generated such that edges represent a valid tree.
//

class Solution {
public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= n; ++i) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        vector<bool> visited(n + 1, false);
        function<long long(int)> dfs = [&](int node) {
            visited[node] = true;
            long long count = isPrime[node] ? 1 : 0;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    count += dfs(neighbor);
                }
            }
            return count;
        };
        
        long long result = 0;
        visited.assign(n + 1, false);
        
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                long long primeCount = dfs(i);
                long long totalNodes = 0;
                for (int neighbor : graph[i]) {
                    if (visited[neighbor]) {
                        totalNodes += dfs(neighbor);
                    }
                }
                result += primeCount * (totalNodes - primeCount);
            }
        }
        
        return result;          
    }
};
