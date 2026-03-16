// Source: https://leetcode.com/problems/cut-off-trees-for-golf-event/   |   Difficulty: Hard
//
// Problem Description:
// You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:
//
//
// 	0 means the cell cannot be walked through.
// 	1 represents an empty cell that can be walked through.
// 	A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
//
//
// In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.
//
// You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).
//
// Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.
//
// Note: The input is generated such that no two trees have the same height, and there is at least one tree needs to be cut off.
//
// Example:
// Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
// Output: 6
// Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
//
// Constraints:
// m == forest.length
// 	n == forest[i].length
// 	1 <= m, n <= 50
// 	0 <= forest[i][j] <= 109
// 	Heights of all trees are distinct.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
// - Hungarian algorithm for solving the assignment problem (matrix, graph, greedy, bfs)
//   • When to use: Finds shortest paths in unweighted graphs or uniform-cost state-space searches. Explores states layer by layer.
//   • Idea: Explores all reachable nodes in a graph layer by layer, finding the shortest path in unweighted graphs. It operates in O(V + E) time complexity.
//   • Invariants: All nodes currently in the queue are at the same distance from the source.; All nodes visited so far have their shortest distance from the source determined.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops.; Incorrectly handling disconnected components.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int cutOffTree(int** forest, int forestSize, int* forestColSize) {
    #define MAX_TREES 2500
    #define DIRECTIONS 4

    typedef struct {
        int x;
        int y;
        int height;
    } Tree;

    // Directions for moving up, down, left, right
    int dirX[DIRECTIONS] = {-1, 1, 0, 0};
    int dirY[DIRECTIONS] = {0, 0, -1, 1};

    // Function to compare trees by height for qsort
    int compareTrees(const void* a, const void* b) {
        return ((Tree*)a)->height - ((Tree*)b)->height;
    }

    // BFS to find shortest path from (sx, sy) to (tx, ty)
    int bfs(int** forest, int forestSize, int* forestColSize, int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return 0;

        bool visited[forestSize][*forestColSize];
        memset(visited, 0, sizeof(visited));

        typedef struct {
            int x;
            int y;
            int steps;
        } Node;

        Node queue[forestSize * (*forestColSize)];
        int front = 0, rear = 0;

        queue[rear++] = (Node){sx, sy, 0};
        visited[sx][sy] = true;

        while (front < rear) {
            Node curr = queue[front++];
            for (int d = 0; d < DIRECTIONS; d++) {
                int nx = curr.x + dirX[d];
                int ny = curr.y + dirY[d];
                if (nx >= 0 && nx < forestSize && ny >= 0 && ny < *forestColSize &&
                    forest[nx][ny] > 0 && !visited[nx][ny]) {
                    if (nx == tx && ny == ty) {
                        return curr.steps + 1;
                    }
                    visited[nx][ny] = true;
                    queue[rear++] = (Node){nx, ny, curr.steps + 1};
                }
            }
        }
        return -1; // Target not reachable
    }

    // Collect all trees
    Tree trees[MAX_TREES];
    int treeCount = 0;
    for (int i = 0; i < forestSize; i++) {
        for (int j = 0; j < *forestColSize; j++) {
            if (forest[i][j] > 1) {
                trees[treeCount++] = (Tree){i, j, forest[i][j]};
            }
        }
    }
    // Sort trees by height
    qsort(trees, treeCount, sizeof(Tree), compareTrees);
    int totalSteps = 0;
    int currX = 0, currY = 0;
    for (int i = 0; i < treeCount; i++) {
        int steps = bfs(forest, forestSize, forestColSize, currX, currY, trees[i].x, trees[i].y);
        if (steps == -1) {
            return -1; // Tree not reachable
        }
        totalSteps += steps;
        currX = trees[i].x;
        currY = trees[i].y;
    }
    return totalSteps;
}
