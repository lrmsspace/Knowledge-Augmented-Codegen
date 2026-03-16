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
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Strongly connected components and the condensation graph (graph, enumeration)
//   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
//   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
//   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
//   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
//   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
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
    // Step 1: Assign unique group IDs to items without a group
    let newGroupId = m;
    for (let i = 0; i < n; i++) {
        if (group[i] === -1) {
            group[i] = newGroupId++;
        }
    }
        
    // Step 2: Build the group and item dependency graphs
    const groupGraph = new Map();
    const itemGraph = new Map();
    const groupInDegree = new Map();
    const itemInDegree = new Map();
    for (let i = 0; i < n; i++) {
        if (!groupGraph.has(group[i])) {
            groupGraph.set(group[i], new Set());
            groupInDegree.set(group[i], 0);
        }
        if (!itemGraph.has(i)) {
            itemGraph.set(i, new Set());
            itemInDegree.set(i, 0);
        }
        for (const beforeItem of beforeItems[i]) {
            itemGraph.get(beforeItem).add(i);
            itemInDegree.set(i, itemInDegree.get(i) + 1);
            if (group[beforeItem] !== group[i]) {
                groupGraph.get(group[beforeItem]).add(group[i]);
                groupInDegree.set(group[i], groupInDegree.get(group[i]) + 1);
            }
        }
    }
        
    // Step 3: Topological sort for groups
    const topologicalSort = (graph, inDegree) => {
        const queue = [];
        for (const [node, degree] of inDegree.entries()) {
            if (degree === 0) {
                queue.push(node);
            }
        }
        const sorted = [];
        while (queue.length > 0) {
            const node = queue.shift();
            sorted.push(node);
            for (const neighbor of graph.get(node) || []) { 
                inDegree.set(neighbor, inDegree.get(neighbor) - 1);
                if (inDegree.get(neighbor) === 0) {
                    queue.push(neighbor);
                }
            }
        }
        return sorted;
    

    };
    const sortedGroups = topologicalSort(groupGraph, groupInDegree);
    if (sortedGroups.length !== groupGraph.size) {
        return []; // Cycle detected in group dependencies
    }
    // Step 4: Topological sort for items within each group
    const groupToItems = new Map();
    for (let i = 0; i < n; i++) {
        if (!groupToItems.has(group[i])) {
            groupToItems.set(group[i], []);
        }
        groupToItems.get(group[i]).push(i);
    }
    const result = [];
    for (const grp of sortedGroups) {
        const items = groupToItems.get(grp) || [];
        const subGraph = new Map();
        const subInDegree = new Map();
        for (const item of items) {
            subGraph.set(item, itemGraph.get(item) || new Set());
            subInDegree.set(item, itemInDegree.get(item) || 0);
        }
        const sortedItems = topologicalSort(subGraph, subInDegree);
        if (sortedItems.length !== items.length) {
            return []; // Cycle detected in item dependencies within the group
        }
        result.push(...sortedItems);
    }
    return result;
};
