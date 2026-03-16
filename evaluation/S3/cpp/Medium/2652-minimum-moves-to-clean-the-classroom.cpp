// Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
//
//
// 	'S': Starting position of the student
// 	'L': Litter that must be collected (once collected, the cell becomes empty)
// 	'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
// 	'X': Obstacle the student cannot pass through
// 	'.': Empty space
//
//
// You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.
//
// Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
//
// Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
//
// Example:
// Input: classroom = ["S.", "XL"], energy = 2
//
// Output: 2
//
// Explanation:
//
//
// 	The student starts at cell (0, 0) with 2 units of energy.
// 	Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
// 	A valid sequence of moves to collect all litter is as follows:
// 	
// 		Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
// 		Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
// 	
// 	
// 	The student collects all the litter using 2 moves. Thus, the output is 2.
//
// Constraints:
// 1 <= m == classroom.length <= 20
// 	1 <= n == classroom[i].length <= 20
// 	classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
// 	1 <= energy <= 50
// 	There is exactly one 'S' in the grid.
// 	There are at most 10 'L' cells in the grid.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - 0-1 BFS (graph, queue, 01-bfs, bfs)
//   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
//   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
//   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
//   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
                
    }
};
