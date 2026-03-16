// Source: https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You have n boxes labeled from 0 to n - 1. You are given four arrays: status, candies, keys, and containedBoxes where:
//
//
// 	status[i] is 1 if the ith box is open and 0 if the ith box is closed,
// 	candies[i] is the number of candies in the ith box,
// 	keys[i] is a list of the labels of the boxes you can open after opening the ith box.
// 	containedBoxes[i] is a list of the boxes you found inside the ith box.
//
//
// You are given an integer array initialBoxes that contains the labels of the boxes you initially have. You can take all the candies in any open box and you can use the keys in it to open new boxes and you also can use the boxes you find in it.
//
// Return the maximum number of candies you can get following the rules above.
//
// Example:
// Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
// Output: 16
// Explanation: You will be initially given box 0. You will find 7 candies in it and boxes 1 and 2.
// Box 1 is closed and you do not have a key for it so you will open box 2. You will find 4 candies and a key to box 1 in box 2.
// In box 1, you will find 5 candies and box 3 but you will not find a key to box 3 so box 3 will remain closed.
// Total number of candies collected = 7 + 4 + 5 = 16 candy.
//
// Constraints:
// n == status.length == candies.length == keys.length == containedBoxes.length
// 	1 <= n <= 1000
// 	status[i] is either 0 or 1.
// 	1 <= candies[i] <= 1000
// 	0 <= keys[i].length <= n
// 	0 <= keys[i][j] < n
// 	All values of keys[i] are unique.
// 	0 <= containedBoxes[i].length <= n
// 	0 <= containedBoxes[i][j] < n
// 	All values of containedBoxes[i] are unique.
// 	Each box is contained in one box at most.
// 	0 <= initialBoxes.length <= n
// 	0 <= initialBoxes[i] < n
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - 0-1 BFS (graph, queue, 01-bfs, bfs)
//   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
//   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
//   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
//   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} status
 * @param {number[]} candies
 * @param {number[][]} keys
 * @param {number[][]} containedBoxes
 * @param {number[]} initialBoxes
 * @return {number}
 */
var maxCandies = function(status, candies, keys, containedBoxes, initialBoxes) {
    let totalCandies = 0;
    const queue = [...initialBoxes];
    const visited = new Set(queue);
    const availableKeys = new Set();

    while (queue.length > 0) {
        const box = queue.shift();
        if (status[box] === 1) {
            totalCandies += candies[box];
            for (const key of keys[box]) {
                availableKeys.add(key);
            }   
            for (const containedBox of containedBoxes[box]) {
                if (!visited.has(containedBox)) {
                    visited.add(containedBox);
                    queue.push(containedBox);
                }
            }
        }
        for (const key of availableKeys) {
            if (key === box) {
                status[box] = 1; // Open the box if we have the key
                break;
            }   

            if (status[key] === 1 && !visited.has(key)) {
                visited.add(key);
                queue.push(key);
            }
        }
    }
    return totalCandies;    
    
};
