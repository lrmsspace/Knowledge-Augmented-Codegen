// Source: https://leetcode.com/problems/detect-cycles-in-2d-grid/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.
//
// A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.
//
// Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.
//
// Return true if any cycle of the same value exists in grid, otherwise, return false.
//
// Example:
// Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
// Output: true
// Explanation: There are two valid cycles shown in different colors in the image below:
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use DFS when you need to explore all reachable nodes from a starting point, find paths, detect cycles, or perform topological sorting in a graph. It is suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs.
//   • Invariants: All nodes currently on the recursion stack (or explicit stack) are part of the current path from the source.; Once a node `v` is marked `visited`, it will not be processed again by the main traversal logic.
//   • Tips: Use a `visited` array or set to track explored nodes.; Pass the parent node in recursive calls to correctly detect cycles.
//   • Pitfalls: Risk of stack overflow for very deep graphs with recursive implementations.; Failure to use a `visited` array leads to infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {character[][]} grid
 * @return {boolean}
 */
var containsCycle = function(grid) {
  const m = grid.length, n = grid[0].length;
  const visited = Array.from({ length: m }, () => Array(n).fill(false));
  
  const directions = [[-1, 0], [1, 0], [0, -1], [0, 1]];
  
  function dfs(x, y, parentX, parentY, char) {
    if (visited[x][y]) {
      return true; // Cycle detected
    }
    
    visited[x][y] = true;
    
    for (const [dx, dy] of directions) {
      const newX = x + dx;
      const newY = y + dy;
      
      if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] === char) {
        if (!(newX === parentX && newY === parentY)) { // Avoid going back to the parent
          if (dfs(newX, newY, x, y, char)) {
            return true; // Cycle detected in the recursive call
          }
        }
      }
    }
    
    return false; // No cycle found in this path
  }
  
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (!visited[i][j]) {
        if (dfs(i, j, -1, -1, grid[i][j])) {
          return true; // Cycle detected
        }
      }
    }
  }
  
  return false; // No cycles found in the entire grid
};
