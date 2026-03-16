// Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
//
//
// 	'.' representing an empty cell.
// 	'#' representing an obstacle.
// 	An uppercase letter ('A'-'Z') representing a teleportation portal.
//
//
// You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
//
// If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
//
// Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
//
// Example:
// Input: matrix = ["A..",".A.","..."]
//
// Output: 2
//
// Explanation:
//
//
//
//
// 	Before the first move, teleport from (0, 0) to (1, 1).
// 	In the first move, move from (1, 1) to (1, 2).
// 	In the second move, move from (1, 2) to (2, 2).
//
// Constraints:
// 1 <= m == matrix.length <= 103
// 	1 <= n == matrix[i].length <= 103
// 	matrix[i][j] is either '#', '.', or an uppercase English letter.
// 	matrix[0][0] is not an obstacle.
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minMoves(String[] matrix) {
        int m = matrix.length;
        int n = matrix[0].length();
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        Map<Character, List<int[]>> portals = new HashMap<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char cell = matrix[i].charAt(j);
                if (Character.isUpperCase(cell)) {
                    portals.computeIfAbsent(cell, k -> new ArrayList<>()).add(new int[]{i, j});
                }
            }
        }

        Deque<int[]> deque = new ArrayDeque<>();
        deque.offerFirst(new int[]{0, 0});
        int[][] dist = new int[m][n];
        for (int[] row : dist) {
            Arrays.fill(row, Integer.MAX_VALUE);
        }
        dist[0][0] = 0;
        Set<Character> usedPortals = new HashSet<>();

        while (!deque.isEmpty()) {
            int[] curr = deque.pollFirst();
            int x = curr[0], y = curr[1];

            if (x == m - 1 && y == n - 1) {
                return dist[x][y];
            }

            char cell = matrix[x].charAt(y);
            if (Character.isUpperCase(cell) && !usedPortals.contains(cell)) {
                usedPortals.add(cell);
                for (int[] portalPos : portals.get(cell)) {
                    int px = portalPos[0], py = portalPos[1];
                    if (dist[px][py] > dist[x][y]) {
                        dist[px][py] = dist[x][y];
                        deque.offerFirst(new int[]{px, py});
                    }
                }
            }

            for (int[] dir : directions) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx].charAt(ny) != '#') {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        deque.offerLast(new int[]{nx, ny});
                    }
                }
            }
            
        }
        return -1; // If the bottom-right corner is not reachable
    }
}
