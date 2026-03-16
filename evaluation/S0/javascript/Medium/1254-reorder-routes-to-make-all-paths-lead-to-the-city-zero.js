// Source: https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to travel between two different cities (this network form a tree). Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.
//
// Roads are represented by connections where connections[i] = [ai, bi] represents a road from city ai to city bi.
//
// This year, there will be a big event in the capital (city 0), and many people want to travel to this city.
//
// Your task consists of reorienting some roads such that each city can visit the city 0. Return the minimum number of edges changed.
//
// It's guaranteed that each city can reach city 0 after reorder.
//
// Example:
// Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
// Output: 3
// Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
//
// Constraints:
// 2 <= n <= 5 * 104
// 	connections.length == n - 1
// 	connections[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//

/**
 * @param {number} n
 * @param {number[][]} connections
 * @return {number}
 */
var minReorder = function(n, connections) {
    const graph = new Map();
    for (const [a, b] of connections) {
        if (!graph.has(a)) graph.set(a, []);
        if (!graph.has(b)) graph.set(b, []);
        graph.get(a).push([b, 1]); // original direction
        graph.get(b).push([a, 0]); // reverse direction
    }
    let changes = 0;
    const visited = new Set();
    const dfs = (node) => {
        visited.add(node);
        for (const [neighbor, direction] of graph.get(node)) {
            if (!visited.has(neighbor)) {
                changes += direction;
                dfs(neighbor);
            }
        }
    };
    dfs(0);
    return changes;
        
};
