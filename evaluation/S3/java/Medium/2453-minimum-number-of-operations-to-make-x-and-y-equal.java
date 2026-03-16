// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers x and y.
//
// In one operation, you can do one of the four following operations:
//
//
// 	Divide x by 11 if x is a multiple of 11.
// 	Divide x by 5 if x is a multiple of 5.
// 	Decrement x by 1.
// 	Increment x by 1.
//
//
// Return the minimum number of operations required to make  x and y equal.
//
// Example:
// Input: x = 26, y = 1
// Output: 3
// Explanation: We can make 26 equal to 1 by applying the following operations: 
// 1. Decrement x by 1
// 2. Divide x by 5
// 3. Divide x by 5
// It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
//
// Constraints:
// 1 <= x, y <= 104
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
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumOperationsToMakeEqual(int x, int y) {
        if (x == y) {
            return 0;
        }

        // Use a queue to perform breadth-first search (BFS)
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.offer(x);
        visited.add(x);

        int operations = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();

            for (int i = 0; i < size; i++) {
                int current = queue.poll();

                if (current == y) {
                    return operations;
                }

                // Generate possible next states
                List<Integer> nextStates = new ArrayList<>();

                if (current % 11 == 0) {
                    nextStates.add(current / 11);
                }
                if (current % 5 == 0) {
                    nextStates.add(current / 5);
                }
                nextStates.add(current - 1);
                nextStates.add(current + 1);

                for (int next : nextStates) {
                    if (next > 0 && !visited.contains(next)) {
                        visited.add(next);
                        queue.offer(next);
                    }
                }
            }

            operations++;
        }

        return -1; // This line should never be reached since x and y are positive integers         
    }
}
