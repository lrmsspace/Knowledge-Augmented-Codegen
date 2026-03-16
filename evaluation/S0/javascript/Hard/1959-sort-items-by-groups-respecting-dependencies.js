// Source: https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/   |   Difficulty: Hard
//
// Problem Description:
// There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.
//
// Return a sorted list of the items such that:
//
//
// 	The items that belong to the same group are next to each other in the sorted list.
// 	There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).
//
//
// Return any solution if there is more than one solution and return an empty list if there is no solution.
//
// Example:
// Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
// Output: [6,3,4,1,5,2,0,7]
//
// Constraints:
// 1 <= m <= n <= 3 * 104
// 	group.length == beforeItems.length == n
// 	-1 <= group[i] <= m - 1
// 	0 <= beforeItems[i].length <= n - 1
// 	0 <= beforeItems[i][j] <= n - 1
// 	i != beforeItems[i][j]
// 	beforeItems[i] does not contain duplicates elements.
//

/**
 * @param {number} n
 * @param {number} m
 * @param {number[]} group
 * @param {number[][]} beforeItems
 * @return {number[]}
 */
var sortItems = function(n, m, group, beforeItems) {
    const groupItems = Array.from({ length: m }, () => []);
    const itemGraph = Array.from({ length: n }, () => []);
    const itemIndegree = new Array(n).fill(0);
    const groupGraph = Array.from({ length: m }, () => []);
    const groupIndegree = new Array(m).fill(0);
    for (let i = 0; i < n; i++) {
        const g = group[i];
        if (g !== -1) {
            groupItems[g].push(i);
        }
        for (const before of beforeItems[i]) {
            itemGraph[before].push(i);
            itemIndegree[i]++;
            const beforeGroup = group[before];
            if (beforeGroup !== -1 && beforeGroup !== g) {
                groupGraph[beforeGroup].push(g);
                groupIndegree[g]++;
            }
        }
    }
    const topologicalSort = (graph, indegree) => {
        const queue = [];
        for (let i = 0; i < indegree.length; i++) {
            if (indegree[i] === 0) {
                queue.push(i);
            }
        }
        const sorted = [];
        while (queue.length > 0) {
            const node = queue.shift();
            sorted.push(node);
            for (const neighbor of graph[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] === 0) {
                    queue.push(neighbor);
                }
            }
        }
        return sorted.length === graph.length ? sorted : [];
    }
    const sortedGroups = topologicalSort(groupGraph, groupIndegree);
    if (sortedGroups.length === 0) {
        return [];
    }
    const result = [];
    for (const g of sortedGroups) {
        const sortedItems = topologicalSort(itemGraph, itemIndegree);
        if (sortedItems.length === 0) {
            return [];
        }
        for (const item of sortedItems) {
            if (group[item] === g) {
                result.push(item);
            }
        }
    }
    return result;  
};
