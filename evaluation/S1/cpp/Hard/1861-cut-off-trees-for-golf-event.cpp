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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size();
        int n = forest[0].size();
        vector<tuple<int, int, int>> trees; // height, x, y
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (forest[i][j] > 1) {
                    trees.emplace_back(forest[i][j], i, j);
                }
            }
        }
        sort(trees.begin(), trees.end());

        auto bfs = [&](int sx, int sy, int tx, int ty) {
            if (sx == tx && sy == ty) return 0;
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            queue<tuple<int, int, int>> q; // x, y, steps
            q.emplace(sx, sy, 0);
            visited[sx][sy] = true;
            vector<int> directions = {0, 1, 0, -1, 0};
            while (!q.empty()) {
                auto [x, y, steps] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d) {
                    int nx = x + directions[d];
                    int ny = y + directions[d + 1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        forest[nx][ny] != 0 && !visited[nx][ny]) {
                        if (nx == tx && ny == ty) {
                            return steps + 1;
                        }
                        visited[nx][ny] = true;
                        q.emplace(nx, ny, steps + 1);
                    }
                }
            }
            return -1;
        };

        int totalSteps = 0;
        int currX = 0, currY = 0;
        for (const auto& [height, tx, ty] : trees) {
            int steps = bfs(currX, currY, tx, ty);
            if (steps == -1) return -1;
            totalSteps += steps;
            currX = tx;
            currY = ty;
        }
        return totalSteps;          
    }
};
