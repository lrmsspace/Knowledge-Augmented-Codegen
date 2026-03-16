// Source: https://leetcode.com/problems/minimum-operations-to-convert-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing distinct numbers, an integer start, and an integer goal. There is an integer x that is initially set to start, and you want to perform operations on x such that it is converted to goal. You can perform the following operation repeatedly on the number x:
//
// If 0 <= x <= 1000, then for any index i in the array (0 <= i < nums.length), you can set x to any of the following:
//
//
// 	x + nums[i]
// 	x - nums[i]
// 	x ^ nums[i] (bitwise-XOR)
//
//
// Note that you can use each nums[i] any number of times in any order. Operations that set x to be out of the range 0 <= x <= 1000 are valid, but no more operations can be done afterward.
//
// Return the minimum number of operations needed to convert x = start into goal, and -1 if it is not possible.
//
// Example:
// Input: nums = [2,4,12], start = 2, goal = 12
// Output: 2
// Explanation: We can go from 2 → 14 → 12 with the following 2 operations.
// - 2 + 12 = 14
// - 14 - 2 = 12
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-109 <= nums[i], goal <= 109
// 	0 <= start <= 1000
// 	start != goal
// 	All the integers in nums are distinct.
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
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumOperations(int* nums, int numsSize, int start, int goal) {
    // We can use a breadth-first search (BFS) approach to find the minimum number of operations needed to convert 'start' to 'goal'.
    // We will use a queue to explore all possible values of 'x' that can be obtained by applying the operations with the numbers in 'nums'.
    // We will also maintain a visited array to avoid processing the same value of 'x' multiple times.

    // Define a queue for BFS and a visited array to track visited values.
    int queue[2001]; // Queue to hold values of x (from 0 to 1000, plus some out-of-range values)
    int visited[2001] = {0}; // Visited array to track which values have been processed
    int front = 0, rear = 0; // Pointers for the queue

    // Enqueue the starting value and mark it as visited
    queue[rear++] = start;
    visited[start] = 1;

    int operations = 0; // Count of operations

    while (front < rear) {
        int size = rear - front; // Number of elements at the current level

        for (int i = 0; i < size; i++) {
            int x = queue[front++]; // Dequeue the next value

            // If we have reached the goal, return the number of operations
            if (x == goal) {
                return operations;
            }

            // Generate new values by applying the operations with each number in nums
            for (int j = 0; j < numsSize; j++) {
                int newX1 = x + nums[j];
                int newX2 = x - nums[j];
                int newX3 = x ^ nums[j];

                // Check if newX1 is within range and not visited
                if (newX1 >= 0 && newX1 <= 1000 && !visited[newX1]) {
                    visited[newX1] = 1;
                    queue[rear++] = newX1;
                }

                // Check if newX2 is within range and not visited
                if (newX2 >= 0 && newX2 <= 1000 && !visited[newX2]) {
                    visited[newX2] = 1;
                    queue[rear++] = newX2;
                }

                // Check if newX3 is within range and not visited       
                if (newX3 >= 0 && newX3 <= 1000 && !visited[newX3]) {
                    visited[newX3] = 1;
                    queue[rear++] = newX3;
                }
            }
            operations++; // Increment operations count for each level in BFS
        }
    }
    return -1; // If goal is not reachable, return -1
}
