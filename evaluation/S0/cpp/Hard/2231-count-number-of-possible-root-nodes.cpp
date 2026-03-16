// Source: https://leetcode.com/problems/count-number-of-possible-root-nodes/   |   Difficulty: Hard
//
// Problem Description:
// Alice has an undirected tree with n nodes labeled from 0 to n - 1. The tree is represented as a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Alice wants Bob to find the root of the tree. She allows Bob to make several guesses about her tree. In one guess, he does the following:
//
//
// 	Chooses two distinct integers u and v such that there exists an edge [u, v] in the tree.
// 	He tells Alice that u is the parent of v in the tree.
//
//
// Bob's guesses are represented by a 2D integer array guesses where guesses[j] = [uj, vj] indicates Bob guessed uj to be the parent of vj.
//
// Alice being lazy, does not reply to each of Bob's guesses, but just says that at least k of his guesses are true.
//
// Given the 2D integer arrays edges, guesses and the integer k, return the number of possible nodes that can be the root of Alice's tree. If there is no such tree, return 0.
//
// Example:
// Input: edges = [[0,1],[1,2],[1,3],[4,2]], guesses = [[1,3],[0,1],[1,0],[2,4]], k = 3
// Output: 3
// Explanation: 
// Root = 0, correct guesses = [1,3], [0,1], [2,4]
// Root = 1, correct guesses = [1,3], [1,0], [2,4]
// Root = 2, correct guesses = [1,3], [1,0], [2,4]
// Root = 3, correct guesses = [1,0], [2,4]
// Root = 4, correct guesses = [1,3], [1,0]
// Considering 0, 1, or 2 as root node leads to 3 correct guesses.
//
// Constraints:
// edges.length == n - 1
// 	2 <= n <= 105
// 	1 <= guesses.length <= 105
// 	0 <= ai, bi, uj, vj <= n - 1
// 	ai != bi
// 	uj != vj
// 	edges represents a valid tree.
// 	guesses[j] is an edge of the tree.
// 	guesses is unique.
// 	0 <= k <= guesses.length
//

class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        unordered_set<long long> guessSet;
        for (const auto& g : guesses) {
            guessSet.insert(((long long)g[0] << 32) | g[1]);
        }
        
        vector<int> parent(n, -1);
        function<void(int, int)> dfsParent = [&](int node, int par) {
            parent[node] = par;
            for (int nei : graph[node]) {
                if (nei != par) {
                    dfsParent(nei, node);
                }
            }
        };
        
        dfsParent(0, -1);
        
        int correctGuesses = 0;
        for (const auto& g : guesses) {
            if (parent[g[1]] == g[0]) {
                correctGuesses++;
            }
        }
        
        int result = 0;
        
        function<void(int, int, int)> dfsReroot = [&](int node, int par, int currCorrect) {
            if (currCorrect >= k) {
                result++;
            }
            for (int nei : graph[node]) {
                if (nei != par) {
                    int nextCorrect = currCorrect;
                    if (guessSet.count(((long long)node << 32) | nei)) {
                        nextCorrect--;
                    }
                    if (guessSet.count(((long long)nei << 32) | node)) {
                        nextCorrect++;
                    }
                    dfsReroot(nei, node, nextCorrect);
                }
            }
        };
        
        dfsReroot(0, -1, correctGuesses);
        
        return result;          
    }
};
