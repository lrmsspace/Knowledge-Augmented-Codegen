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
// Helpful references (internal KB):
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

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
    
    // Assign items to their respective groups
    for (let i = 0; i < n; i++) {
        if (group[i] !== -1) {
            groupItems[group[i]].push(i);
        }
    }

    // Build item dependency graph and calculate indegrees
    for (let i = 0; i < n; i++) {
        for (const before of beforeItems[i]) {
            if (group[before] === group[i]) {
                itemGraph[before].push(i);
                itemIndegree[i]++;
            } else {
                const fromGroup = group[before];
                const toGroup = group[i];
                if (fromGroup !== -1 && toGroup !== -1 && fromGroup !== toGroup) {
                    groupGraph[fromGroup].push(toGroup);
                    groupIndegree[toGroup]++;
                }
            }
        }
    }

    // Topological sort within each group
    const sortedItems = [];
    const queue = [];
    
    for (let i = 0; i < n; i++) {
        if (itemIndegree[i] === 0) {
            queue.push(i);
        }
    }

    while (queue.length > 0) {
        const current = queue.shift();
        sortedItems.push(current);
        
        for (const neighbor of itemGraph[current]) {
            itemIndegree[neighbor]--;
            if (itemIndegree[neighbor] === 0) {
                queue.push(neighbor);
            }
        }
    }

    if (sortedItems.length !== n) return [];

    // Topological sort among groups
    const sortedGroups = [];
    const groupQueue = [];
    
    for (let i = 0; i < m; i++) {
        if (groupIndegree[i] === 0) {
            groupQueue.push(i);
        }
    }

    while (groupQueue.length > 0) {
        const current = groupQueue.shift();
        sortedGroups.push(current);
        
        for (const neighbor of groupGraph[current]) {
            groupIndegree[neighbor]--;
            if (groupIndegree[neighbor] === 0) {
                groupQueue.push(neighbor);
            }
        }
    }

    if (sortedGroups.length !== m) return [];

    // Combine sorted items in order of sorted groups
    const result = [];
    
    for (const g of sortedGroups) {
        for (const item of groupItems[g]) {
            result.push(item);
        }
    }

    return result;
};
