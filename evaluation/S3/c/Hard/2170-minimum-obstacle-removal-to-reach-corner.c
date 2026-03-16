// Source: https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
//
//
// 	0 represents an empty cell,
// 	1 represents an obstacle that may be removed.
//
//
// You can move up, down, left, or right from and to an empty cell.
//
// Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).
//
// Example:
// Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
// Output: 2
// Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
// It can be shown that we need to remove at least 2 obstacles, so we return 2.
// Note that there may be other ways to remove 2 obstacles to create a path.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - 0-1 BFS (graph, queue, 01-bfs, bfs)
//   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
//   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
//   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
//   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumObstacles(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int* dist = (int*)malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++) dist[i] = INT_MAX;
    dist[0] = 0;

    typedef struct {
        int x, y;
    } Point;

    Point* deque = (Point*)malloc(m * n * sizeof(Point));
    int front = 0, back = 0;
    deque[back++] = (Point){0, 0};

    while (front < back) {
        Point current = deque[front++];
        int currentDist = dist[current.x * n + current.y];

        for (int i = 0; i < 4; i++) {
            int newX = current.x + directions[i][0];
            int newY = current.y + directions[i][1];

            if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                int newDist = currentDist + grid[newX][newY];
                if (newDist < dist[newX * n + newY]) {
                    dist[newX * n + newY] = newDist;
                    if (grid[newX][newY] == 1) {
                        deque[back++] = (Point){newX, newY};
                    } else {
                        memmove(&deque[front + 1], &deque[front], (back - front) * sizeof(Point));
                        deque[front] = (Point){newX, newY};
                        back++;
                    }
                }
            }
        }
    }

    int result = dist[(m - 1) * n + (n - 1)];
    free(dist);
    free(deque);
    return result;      
}
