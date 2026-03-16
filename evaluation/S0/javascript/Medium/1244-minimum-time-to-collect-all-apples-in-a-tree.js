// Source: https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given an undirected tree consisting of n vertices numbered from 0 to n-1, which has some apples in their vertices. You spend 1 second to walk over one edge of the tree. Return the minimum time in seconds you have to spend to collect all apples in the tree, starting at vertex 0 and coming back to this vertex.
//
// The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi. Additionally, there is a boolean array hasApple, where hasApple[i] = true means that vertex i has an apple; otherwise, it does not have any apple.
//
// Example:
// Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
// Output: 8 
// Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai < bi <= n - 1
// 	hasApple.length == n
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {boolean[]} hasApple
 * @return {number}
 */
var minTime = function(n, edges, hasApple) {
    const tree = Array.from({ length: n }, () => []);
    for (const [a, b] of edges) {
        tree[a].push(b);
        tree[b].push(a);
    }
    const visited = new Set();
    const dfs = (node) => {
        visited.add(node);
        let totalTime = 0;
        for (const neighbor of tree[node]) {
            if (!visited.has(neighbor)) {
                const timeFromChild = dfs(neighbor);
                if (timeFromChild > 0 || hasApple[neighbor]) {
                    totalTime += timeFromChild + 2;
                }
            }
        }
        return totalTime;
    };
    return dfs(0);  
            
};
