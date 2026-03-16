// Source: https://leetcode.com/problems/number-of-operations-to-make-network-connected/   |   Difficulty: Medium
//
// Problem Description:
// There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where connections[i] = [ai, bi] represents a connection between computers ai and bi. Any computer can reach any other computer directly or indirectly through the network.
//
// You are given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.
//
// Return the minimum number of times you need to do this in order to make all the computers connected. If it is not possible, return -1.
//
// Example:
// Input: n = 4, connections = [[0,1],[0,2],[1,2]]
// Output: 1
// Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= connections.length <= min(n * (n - 1) / 2, 105)
// 	connections[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated connections.
// 	No two computers are connected by more than one cable.
//

/**
 * @param {number} n
 * @param {number[][]} connections
 * @return {number}
 */
var makeConnected = function(n, connections) {
    if (connections.length < n - 1) return -1;
    const parent = Array.from({ length: n }, (_, i) => i);
    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };  
    const union = (x, y) => {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            parent[rootY] = rootX;
        }
    };  
    for (const [a, b] of connections) {
        union(a, b);
    }
    const uniqueParents = new Set();
    for (let i = 0; i < n; i++) {
        uniqueParents.add(find(i));
    }
    return uniqueParents.size - 1;
            
};
