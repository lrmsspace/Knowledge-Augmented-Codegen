// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].
//
// You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.
//
// Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
//
// Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
//
// Example:
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert the string "abcd" to string "acbe":
// - Change value at index 1 from 'b' to 'c' at a cost of 5.
// - Change value at index 2 from 'c' to 'e' at a cost of 1.
// - Change value at index 2 from 'e' to 'b' at a cost of 2.
// - Change value at index 3 from 'd' to 'e' at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28.
// It can be shown that this is the minimum possible cost.
//
// Constraints:
// 1 <= source.length == target.length <= 105
// 	source, target consist of lowercase English letters.
// 	1 <= cost.length == original.length == changed.length <= 2000
// 	original[i], changed[i] are lowercase English letters.
// 	1 <= cost[i] <= 106
// 	original[i] != changed[i]
//

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        const int ALPHABET_SIZE = 26;
        const int INF = 1e9;

        // Build the cost graph
        vector<vector<int>> graph(ALPHABET_SIZE, vector<int>(ALPHABET_SIZE, INF));
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            graph[i][i] = 0;
        }
        for (size_t i = 0; i < original.size(); ++i) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            graph[u][v] = min(graph[u][v], cost[i]);
        }

        // Floyd-Warshall algorithm to find the minimum cost between all pairs of characters
        for (int k = 0; k < ALPHABET_SIZE; ++k) {
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                for (int j = 0; j < ALPHABET_SIZE; ++j) {
                    if (graph[i][k] < INF && graph[k][j] < INF) {
                        graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                    }
                }
            }
        }

        // Calculate the total cost to convert source to target
        long long totalCost = 0;
        for (size_t i = 0; i < source.length(); ++i) {
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            if (graph[u][v] == INF) {
                return -1; // Impossible to convert
            }
            totalCost += graph[u][v];
        }

        return totalCost;           
    }
};
