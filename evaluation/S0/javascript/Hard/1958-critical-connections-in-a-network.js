// Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
//
// Problem Description:
// There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
//
// A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
//
// Return all critical connections in the network in any order.
//
// Example:
// Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
// Output: [[1,3]]
// Explanation: [[3,1]] is also accepted.
//
// Constraints:
// 2 <= n <= 105
// 	n - 1 <= connections.length <= 105
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated connections.
//

/**
 * @param {number} n
 * @param {number[][]} connections
 * @return {number[][]}
 */
var criticalConnections = function(n, connections) {
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v] of connections) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const discovery = new Array(n).fill(-1);
    const low = new Array(n).fill(-1);
    const result = [];
    let time = 0;
    const dfs = (node, parent) => {
        discovery[node] = low[node] = time++;
        for (const neighbor of graph[node]) {
            if (neighbor === parent) {
                continue;
            }
            if (discovery[neighbor] === -1) {
                dfs(neighbor, node);
                low[node] = Math.min(low[node], low[neighbor]);
                if (low[neighbor] > discovery[node]) {
                    result.push([node, neighbor]);
                }
            } else {
                low[node] = Math.min(low[node], discovery[neighbor]);
            }
        }
    }
    dfs(0, -1);
    return result;  
};
