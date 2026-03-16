// Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
//
// Problem Description:
// A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
//
// The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
//
// Your task is to move the box 'B' to the target position 'T' under the following rules:
//
//
// 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
// 	The character '.' represents the floor which means a free cell to walk.
// 	The character '#' represents the wall which means an obstacle (impossible to walk there).
// 	There is only one box 'B' and one target cell 'T' in the grid.
// 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
// 	The player cannot walk through the box.
//
//
// Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [["#","#","#","#","#","#"],
//                ["#","T","#","#","#","#"],
//                ["#",".",".","B",".","#"],
//                ["#",".","#","#",".","#"],
//                ["#",".",".",".","S","#"],
//                ["#","#","#","#","#","#"]]
// Output: 3
// Explanation: We return only the number of times the box is pushed.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
// 	There is only one character 'S', 'B', and 'T' in the grid.
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minPushBox(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int[] box = new int[2];
        int[] target = new int[2];
        int[] player = new int[2];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'B') {
                    box[0] = i;
                    box[1] = j;
                } else if (grid[i][j] == 'T') {
                    target[0] = i;
                    target[1] = j;
                } else if (grid[i][j] == 'S') {
                    player[0] = i;
                    player[1] = j;
                }
            }
        }
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        Deque<int[]> deque = new ArrayDeque<>();
        boolean[][][] visited = new boolean[m][n][4];
        for (int d = 0; d < 4; d++) {
            visited[box[0]][box[1]][d] = true;
            deque.offerFirst(new int[]{box[0], box[1], player[0], player[1], d, 0});
        }
        while (!deque.isEmpty()) {
            int[] state = deque.pollFirst();
            int boxX = state[0];
            int boxY = state[1];
            int playerX = state[2];
            int playerY = state[3];
            int dir = state[4];
            int pushes = state[5];

            if (boxX == target[0] && boxY == target[1]) {
                return pushes;
            }

            // Try to push the box
            int newBoxX = boxX + directions[dir][0];
            int newBoxY = boxY + directions[dir][1];
            int requiredPlayerX = boxX - directions[dir][0];
            int requiredPlayerY = boxY - directions[dir][1];

            if (newBoxX >= 0 && newBoxX < m && newBoxY >= 0 && newBoxY < n &&
                grid[newBoxX][newBoxY] != '#' &&
                requiredPlayerX >= 0 && requiredPlayerX < m && requiredPlayerY >= 0 && requiredPlayerY < n &&
                grid[requiredPlayerX][requiredPlayerY] != '#') {

                if (!visited[newBoxX][newBoxY][dir]) {
                    visited[newBoxX][newBoxY][dir] = true;
                    deque.offerLast(new int[]{newBoxX, newBoxY, boxX, boxY, dir, pushes + 1});
                }
            }

            // Try to move the player without pushing the box
            for (int newDir = 0; newDir < 4; newDir++) {
                if (newDir == dir) continue; // Skip the direction of pushing

                int newPlayerX = playerX + directions[newDir][0];
                int newPlayerY = playerY + directions[newDir][1];

                if (newPlayerX >= 0 && newPlayerX < m && newPlayerY >= 0 && newPlayerY < n &&
                    grid[newPlayerX][newPlayerY] != '#' &&
                    !(newPlayerX == boxX && newPlayerY == boxY)) {

                    if (!visited[boxX][boxY][newDir]) {
                        visited[boxX][boxY][newDir] = true;
                        deque.offerFirst(new int[]{boxX, boxY, newPlayerX, newPlayerY, newDir, pushes});
                    }
                }
            }
        }
        return -1;    
    }
}
