// Source: https://leetcode.com/problems/race-car/   |   Difficulty: Hard
//
// Problem Description:
// Your car starts at position 0 and speed +1 on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions 'A' (accelerate) and 'R' (reverse):
//
//
// 	When you get an instruction 'A', your car does the following:
//
// 	
// 		position += speed
// 		speed *= 2
// 	
// 	
// 	When you get an instruction 'R', your car does the following:
// 	
// 		If your speed is positive then speed = -1
// 		otherwise speed = 1
// 	
// 	Your position stays the same.
//
//
// For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 --> 3, and your speed goes to 1 --> 2 --> 4 --> -1.
//
// Given a target position target, return the length of the shortest sequence of instructions to get there.
//
// Example:
// Input: target = 3
// Output: 2
// Explanation: 
// The shortest instruction sequence is "AA".
// Your position goes from 0 --> 1 --> 3.
//
// Constraints:
// 1 <= target <= 104
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int racecar(int target) {
        // BFS approach
        class State {
            int position;
            int speed;

            State(int position, int speed) {
                this.position = position;
                this.speed = speed;
            }
        }

        Queue<State> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();

        queue.offer(new State(0, 1));
        visited.add("0,1");

        int steps = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                State current = queue.poll();

                if (current.position == target) {
                    return steps;
                }

                // Accelerate
                State accelerate = new State(current.position + current.speed, current.speed * 2);
                String accKey = accelerate.position + "," + accelerate.speed;
                if (!visited.contains(accKey) && Math.abs(accelerate.position) <= 2 * target) {
                    visited.add(accKey);
                    queue.offer(accelerate);
                }

                // Reverse
                int newSpeed = current.speed > 0 ? -1 : 1;
                State reverse = new State(current.position, newSpeed);
                String revKey = reverse.position + "," + reverse.speed;
                if (!visited.contains(revKey) && Math.abs(reverse.position) <= 2 * target) {
                    visited.add(revKey);
                    queue.offer(reverse);
                }
            }
            steps++;
        }

        return -1; // This line should never be reached         
    }
}
