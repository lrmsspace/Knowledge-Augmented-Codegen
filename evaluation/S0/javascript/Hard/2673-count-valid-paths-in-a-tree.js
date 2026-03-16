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

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countPaths = function(n, edges) {
    const isPrime = Array(n + 1).fill(true);
    isPrime[0] = isPrime[1] = false;
    for (let i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (let j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    const graph = Array.from({ length: n + 1 }, () => []);
    for (const [u, v] of edges) {   
        graph[u].push(v);
        graph[v].push(u);
    }
    let count = 0;
    const visited = Array(n + 1).fill(false);
    const dfs = (node, primeCount) => {
        visited[node] = true;
        if (primeCount === 1) {
            count++;
        }
        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, primeCount + (isPrime[neighbor] ? 1 : 0));
            }
        }
        visited[node] = false;
    }
    for (let i = 1; i <= n; i++) {
        dfs(i, isPrime[i] ? 1 : 0);
    }
    return count / 2;   
};
