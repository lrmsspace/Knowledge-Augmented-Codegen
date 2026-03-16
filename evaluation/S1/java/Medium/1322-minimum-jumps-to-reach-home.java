// Source: https://leetcode.com/problems/minimum-jumps-to-reach-home/   |   Difficulty: Medium
//
// Problem Description:
// A certain bug's home is on the x-axis at position x. Help them get there from position 0.
//
// The bug jumps according to the following rules:
//
//
// 	It can jump exactly a positions forward (to the right).
// 	It can jump exactly b positions backward (to the left).
// 	It cannot jump backward twice in a row.
// 	It cannot jump to any forbidden positions.
//
//
// The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
//
// Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
//
// Example:
// Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
// Output: 3
// Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
//
// Constraints:
// 1 <= forbidden.length <= 1000
// 	1 <= a, b, forbidden[i] <= 2000
// 	0 <= x <= 2000
// 	All the elements in forbidden are distinct.
// 	Position x is not forbidden.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumJumps(int[] forbidden, int a, int b, int x) {
        final int LIMIT = 6000;
        boolean[][] visited = new boolean[LIMIT + 1][2];
        for (int pos : forbidden) {
            if (pos <= LIMIT) {
                visited[pos][0] = true;
                visited[pos][1] = true;
            }
        }

        java.util.Queue<int[]> queue = new java.util.LinkedList<>();
        queue.offer(new int[]{0, 0, 0}); // position, jumps, last move was backward (0/1)
        visited[0][0] = true;

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int position = curr[0];
            int jumps = curr[1];
            int lastBackward = curr[2];

            if (position == x) {
                return jumps;
            }

            // Jump forward
            int forwardPos = position + a;
            if (forwardPos <= LIMIT && !visited[forwardPos][0]) {
                visited[forwardPos][0] = true;
                queue.offer(new int[]{forwardPos, jumps + 1, 0});
            }

            // Jump backward
            if (lastBackward == 0) { // can only jump backward if last move was not backward
                int backwardPos = position - b;
                if (backwardPos >= 0 && !visited[backwardPos][1]) {
                    visited[backwardPos][1] = true;
                    queue.offer(new int[]{backwardPos, jumps + 1, 1});
                }
            }
        }

        return -1; // not reachable         
    }
}
