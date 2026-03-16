// Source: https://leetcode.com/problems/loud-and-rich/   |   Difficulty: Medium
//
// Problem Description:
// There is a group of n people labeled from 0 to n - 1 where each person has a different amount of money and a different level of quietness.
//
// You are given an array richer where richer[i] = [ai, bi] indicates that ai has more money than bi and an integer array quiet where quiet[i] is the quietness of the ith person. All the given data in richer are logically correct (i.e., the data will not lead you to a situation where x is richer than y and y is richer than x at the same time).
//
// Return an integer array answer where answer[x] = y if y is the least quiet person (that is, the person y with the smallest value of quiet[y]) among all people who definitely have equal to or more money than the person x.
//
// Example:
// Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
// Output: [5,5,2,5,4,5,6,7]
// Explanation: 
// answer[0] = 5.
// Person 5 has more money than 3, which has more money than 1, which has more money than 0.
// The only person who is quieter (has lower quiet[x]) is person 7, but it is not clear if they have more money than person 0.
// answer[7] = 7.
// Among all people that definitely have equal to or more money than person 7 (which could be persons 3, 4, 5, 6, or 7), the person who is the quietest (has lower quiet[x]) is person 7.
// The other answers can be filled out with similar reasoning.
//
// Constraints:
// n == quiet.length
// 	1 <= n <= 500
// 	0 <= quiet[i] < n
// 	All the values of quiet are unique.
// 	0 <= richer.length <= n * (n - 1) / 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	All the pairs of richer are unique.
// 	The observations in richer are all logically consistent.
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} richer
 * @param {number[]} quiet
 * @return {number[]}
 */
var loudAndRich = function(richer, quiet) {
    const n = quiet.length;
    const graph = Array.from({ length: n }, () => []);      // Adjacency list for the graph 
    for (const [a, b] of richer) {
        graph[b].push(a);  // Build reverse graph: if a is richer than b, then b -> a in the reverse graph
    }
    
    const memo = Array(n).fill(-1);  // Memoization array to store the least quiet person in each subtree
    
    const dfs = (node) => {
        if (memo[node] !== -1) return memo[node];
        let quietest = node;  // Initially assume the current node is the quietest in its subtree
        for (const neighbor of graph[node]) {
            const quietestNeighbor = dfs(neighbor);
            if (quiet[quietestNeighbor] < quiet[quietest]) {
                quietest = quietestNeighbor;
            }
        }
        memo[node] = quietest;
        return quietest;
    };
    
    const result = [];
    for (let i = 0; i < n; i++) {
        result.push(dfs(i));
    }
    return result;
};
