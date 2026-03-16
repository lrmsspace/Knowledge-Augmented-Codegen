// Source: https://leetcode.com/problems/perfect-squares/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the least number of perfect square numbers that sum to n.
//
// A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
//
// Example:
// Input: n = 12
// Output: 3
// Explanation: 12 = 4 + 4 + 4.
//
// Constraints:
// 1 <= n <= 104
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when you need to find the shortest path (in terms of number of edges) from a source node to all other reachable nodes in an unweighted graph. It is also suitable for exploring a graph layer by layer.
//   • Idea: BFS systematically explores a graph level by level, starting from a source node, ensuring all nodes at a given distance are visited before moving to the next distance level. It operates in O(N + M) time for N vertices and M edges.
//   • Invariants: All nodes currently in the queue are at the same or adjacent distance level from the source.; The 'used' array accurately reflects all nodes that have been added to the queue for processing.
//   • Tips: Always use a queue to maintain the order of nodes to visit.; Utilize a 'visited' array or set to prevent revisiting nodes and infinite loops.
//   • Pitfalls: Does not find shortest paths in weighted graphs unless weights are 0 or 1 (use Dijkstra for general weighted graphs).; Forgetting to mark nodes as visited can lead to incorrect results or TLE.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numSquares(int n) {
    int squares[100], count = 0;
    for (int i = 1; i * i <= n; i++) {
        squares[count++] = i * i;
    }

    int queue[10000], front = 0, rear = 0;
    int visited[10001] = {0};
    queue[rear++] = n;
    visited[n] = 1;

    int level = 0;
    while (front < rear) {
        int size = rear - front;
        level++;
        for (int i = 0; i < size; i++) {
            int curr = queue[front++];
            for (int j = 0; j < count; j++) {
                int next = curr - squares[j];
                if (next < 0) break;
                if (next == 0) return level;
                if (!visited[next]) {
                    visited[next] = 1;
                    queue[rear++] = next;
                }
            }
        }
    }
    return level;       
}
