// Source: https://leetcode.com/problems/validate-binary-tree-nodes/   |   Difficulty: Medium
//
// Problem Description:
// You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
//
// If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
//
// Note that the nodes have no values and that we only use the node numbers in this problem.
//
// Example:
// Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
// Output: true
//
// Constraints:
// n == leftChild.length == rightChild.length
// 	1 <= n <= 104
// 	-1 <= leftChild[i], rightChild[i] <= n - 1
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int bfs(int rootIndex, int[] leftChild, int[] rightChild, boolean[] visited) {
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(rootIndex);
        visited[rootIndex] = true;
        int visitedCount = 1;

        while (!queue.isEmpty()) {
            int currentNode = queue.poll();

            int left = leftChild[currentNode];
            if (left != -1 && !visited[left]) {
                visited[left] = true;
                visitedCount++;
                queue.offer(left);
            }

            int right = rightChild[currentNode];
            if (right != -1 && !visited[right]) {
                visited[right] = true;
                visitedCount++;
                queue.offer(right);
            }
        }

        return visitedCount;
    }
    public boolean validateBinaryTreeNodes(int n, int[] leftChild, int[] rightChild) {
        int[] inDegree = new int[n];
        for (int i = 0; i < n; i++) {
            if (leftChild[i] != -1) {
                inDegree[leftChild[i]]++;
                if (inDegree[leftChild[i]] > 1) {
                    return false; // A node has more than one parent
                }
            }
            if (rightChild[i] != -1) {
                inDegree[rightChild[i]]++;
                if (inDegree[rightChild[i]] > 1) {
                    return false; // A node has more than one parent
                }
            }
        }

        int rootCount = 0;
        int rootIndex = -1;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                rootCount++;
                rootIndex = i;
            }
        }

        if (rootCount != 1) {
            return false; // There should be exactly one root
        }

        boolean[] visited = new boolean[n];
        int visitedCount = bfs(rootIndex, leftChild, rightChild, visited);

        return visitedCount == n; // All nodes must be visited          
    }
}
